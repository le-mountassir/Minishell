/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_fds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:32:14 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/19 11:56:18 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	redir_output(t_shell *s)
{
	if (s->file.over_write)
		s->file.fdout = open(s->file.outfile,
				O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (s->file.append_f)
		s->file.fdout = open(s->file.outfile,
				O_CREAT | O_RDWR | O_APPEND, 0644);
	if (s->file.fdout < 0)
		bash_error_w_filename(s, s->file.outfile);
	ft_free(s->file.outfile);
}

static void	redir_input(t_shell *s)
{
	if (s->file.input_fd)
		s->file.fdin = open(s->file.input_fd, O_RDONLY);
	if (s->file.fdin < 0)
		bash_error_w_filename(s, s->file.input_fd);
	ft_free(s->file.input_fd);
}

void	checkfile_redir(t_shell *s)
{
	if (s->file.stopword)
		get_heredoc(s);
	else if (s->file.input_fd)
		redir_input(s);
	if (s->file.outfile)
		redir_output(s);
}
static void	switch_pipefds(int *fd, int new_fd, int REDIR)
{
	if (*fd == REDIR)
		*fd = new_fd;
	else
		close(new_fd);
}

void	get_fds(t_shell *s, int i, int *pipe_fd)
{
	close(pipe_fd[READ]);
	checkfile_redir(s); // checks if there isa a redir if yes we change the fds
	if (i > 0) // i == 0 it means theres no pipe before
		switch_pipefds(&s->file.fdin,
			s->pipe_two[READ], READ);
	if (i != s->num_of_cmds - 1)
		switch_pipefds(&s->file.fdout,
			pipe_fd[WRITE], WRITE);
	else
		close(pipe_fd[WRITE]);
}

