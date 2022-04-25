/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:32:27 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/04/25 18:17:44 by ahel-mou         ###   ########.fr       */
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

static void	cmd_execution(t_shell *shell, int i, int *pipe_fd)
{
	int		j;

	j = -1;
	get_fds(shell, i, pipe_fd);
	dup_stdinout(shell);
	if (home_made(shell, i))
		exit(0);
	exec_cmd(shell, j);
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
