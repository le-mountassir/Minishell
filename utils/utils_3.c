/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:32:35 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/21 13:34:03 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fork_failed(t_shell *s)
{
	if (s->pipe_two)
		free(s->pipe_two);
	free_arr(s->cmd_with_args);
	ft_putstr_fd("Fork", 2);
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
	int time = 1000000;
	i = 0;
	while (i + time > 0)
		i--;
}

void	free_redir(t_shell *s)
{
	if (s->file.stopword)
		ft_free(s->file.stopword);
	if (s->file.input_fd)
		ft_free(s->file.input_fd);
	if (s->file.outfile)
		ft_free(s->file.outfile);
}

