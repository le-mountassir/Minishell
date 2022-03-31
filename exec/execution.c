/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:32:27 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/29 11:18:58 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	parent_process(t_shell *shell, int i, int *pipe_fd)
{
	close(pipe_fd[WRITE]);
	if (i > 0)
		close(shell->pipe_two[READ]);
	if (i == shell->num_of_cmds - 1)
	{
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

//exec is where we call execve
// if the cmd wasnt executed and the !cmdnotfound it means line:83
// -->that there is a file but we cant execute it.
static void	cmd_execution(t_shell *shell, int i, int *pipe_fd)
{
	int		j;
	int		check;

	check = 1;
	j = -1;
	get_fds(shell, i, pipe_fd);
	dup_stdinout(shell);
	if (home_made(shell, i))
		check = 0;
	exec_cmd(shell, j, check);
	if (!shell->cmdnotfound && shell->cmd_with_args[0] && check)
		ft_putstr_fd("File not executable\n", 2);
	close(shell->file.fdin);
	close(shell->file.fdout);
	usleep(100);
}

static void	start_processing(t_shell *shell, int i, int *pipe_fd)
{
	g_cld_proc = fork();
	if (g_cld_proc < 0)
		fork_failed(shell);
	if (g_cld_proc == 0)
		cmd_execution(shell, i, pipe_fd);
	else if (g_cld_proc > 0)
		parent_process(shell, i, pipe_fd);
}

// here we check if the command is pipeabloe or not
// --> means that we can pass its output to the next cmd
// --> heredoc with no command after it is not pipeable
// split the cmd to a 2d_rr with its cmd_with_argss line:128
		// signal(SIGQUIT, handle_sigquit); f loop
void	execution(t_shell *shell)
{
	int		pipe_fd[2];
	int		i;

	i = -1;
	while (shell->cmd[++i])
	{
		if (pipe(pipe_fd) < 0)
			ft_exit(shell, "Pipe");
		reset_shell(shell);
		shell->cmd_with_args = parse_cmd(shell, i);
		if (shell->input_error)
			break ;
		if ((!shell->cmd_with_args[0] && !shell->file.here_doc)
			|| only_hrdoc_with_nocmd(shell)
			|| not_executable_cmd(shell, shell->cmd_with_args[0]))
		{
			free_arr(shell->cmd_with_args);
			continue ;
		}
		start_processing(shell, i, pipe_fd);
		free_arr(shell->cmd_with_args);
	}
}
