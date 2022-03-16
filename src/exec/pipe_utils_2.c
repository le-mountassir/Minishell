/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:32:35 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/13 12:48:05 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fork_failed(t_shell *s)
{
	if (s->pipe_two)
		free(s->pipe_two);
	free_arr(s->cmd_with_args);
	perror("Fork");
	exit(1);
}

void	close_fds(t_shell *s)
{
	if (s->file.fdin != READ)
	{
		close(s->file.fdin);
		s->file.fdin = READ;
	}
	if (s->file.fdout != WRITE)
	{
		close(s->file.fdout);
		s->file.fdout = WRITE;
	}
}

void	wait_pid(void)
{
	int	i;

	i = 0;
	while (i + TIME > 0)
		i--;
}

static void	switch_pipefds(int *fd, int new_fd, int REDIR)
{
	if (*fd == REDIR)
		*fd = new_fd;
	else
		close(new_fd);
}

void	get_fds(t_shell *s, int i)
{
	close(s->pipe_fd[READ]);
	checkfile_redir(s);
	if (i > 0) // i > 0 bcs the 0 arg is the file that we gonna read from and i[1] == << ; <
		switch_pipefds(&s->file.fdin,
			s->pipe_two[READ], READ);
	if (i != s->num_of_cmds - 1)
		switch_pipefds(&s->file.fdout,
			s->pipe_fd[WRITE], WRITE);
	else
		close(s->pipe_fd[WRITE]);
}
