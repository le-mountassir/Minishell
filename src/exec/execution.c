/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:32:27 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/15 16:04:45 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	switch_pipe(t_shell *shell, int *curr_pipe)
{
	if (shell->pipe_two)
		free(shell->pipe_two);
	shell->pipe_two = malloc(sizeof(int) * 2);
	shell->pipe_two[READ] = curr_pipe[READ];
	shell->pipe_two[WRITE] = curr_pipe[WRITE];
}

static void	parent_process(t_shell *shell, int i,int *pipe_fd)
{
	close(pipe_fd[WRITE]);
	if (i > 0)
		close(shell->pipe_two[READ]);
	if (i == shell->num_of_cmds - 1)
	{
		free(shell->pipe_two);
		shell->pipe_two = 0;
		close(pipe_fd[READ]);
	}
	else
		switch_pipe(shell, pipe_fd);
	close_fds(shell);
	free_redir(shell);
}

static void	dup_stdinout(t_shell *shell)
{
	if (shell->file.fdin != READ)
	{
		if (dup2(shell->file.fdin, READ) < 0)
			exit(1);
		close(shell->file.fdin);
	}
	if (shell->file.fdout != WRITE)
	{
		if (dup2(shell->file.fdout, WRITE) < 0)
			exit(1);
		close(shell->file.fdout);
	}
}

static void	cmd_execution(t_shell *shell, int i, int *pipe_fd)
{
	int		j;
	char	*cmd;

	j = 0;
	get_fds(shell, i, pipe_fd);
	dup_stdinout(shell);
	// if the user gave us a path we will execute it here when exec finbish it will kill the c_process
	if (shell->cmd_with_args[0] && !shell->input_error) 
		execve(shell->cmd_with_args[0], shell->cmd_with_args, shell->our_env);
	// if he gave us cmd we loop through the paths and join them with the cmd and exec
	while (!shell->input_error && shell->cmd_with_args[0] && shell->path[j])
	{
		cmd = ft_join(shell->path[j], shell->cmd_with_args[0]);
		if (!cmd)
			exit(1);
		execve(cmd, shell->cmd_with_args, shell->our_env);
		free(cmd);
		j++;
	}
	// if the cmd wasnt executed and the !cmdnotfound it means that there is a file but we cant execute it
	if (!shell->cmdnotfound && shell->cmd_with_args[0])
		ft_putstr_fd("File not executable\n", 2);
	close(shell->file.fdin);
	close(shell->file.fdout);
	wait_pid();
}

void	execution(t_shell *shell)
{
	int		pipe_fd[2];
	int i = -1;
	while (shell->cmd[++i])
	{
		if (pipe(pipe_fd) < 0)
			ft_exit(shell, "Pipe");
		// signal(SIGQUIT, handle_sigquit);
		reset_shell(shell);
		shell->cmd_with_args = parse_cmd(shell, i); // split the cmd to a 2d_rr with its cmd_with_argss
		if (shell->syntax_error)
			break ;
		// here we check if the command is pipeabloe or not means that we can pass its output to the next cmd
		// our homemade_cmd ar not pipeable means we just skip them
		// heredoc with no command after it is not pipeable
		if (not_pipeable_cmd(shell))
			continue ; // we skip to the next command
		g_proc = fork();
		if (g_proc < 0)
			fork_failed(shell);
		if (g_proc == 0) // start child process
			cmd_execution(shell, i, pipe_fd);
		else if (g_proc > 0)
			parent_process(shell, i, pipe_fd);
		free_arr(shell->cmd_with_args);
	}
}
