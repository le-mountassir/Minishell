/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:32:35 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/29 18:09:20 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fork_failed(t_shell *s)
{
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

void	free_redir(t_shell *s)
{
	if (s->file.stopword)
		ft_free(s->file.stopword);
	if (s->file.input_fd)
		ft_free(s->file.input_fd);
	if (s->file.outfile)
		ft_free(s->file.outfile);
}

void	switch_pipe(t_shell *shell, int *curr_pipe)
{
	shell->pipe_two[READ] = curr_pipe[READ];
	shell->pipe_two[WRITE] = curr_pipe[WRITE];
}

void	skip_to_option(char *cmd, t_echo *e_vars, char **parsed_cmd)
{
	int	i;

	i = 1;
	e_vars->i = 4;
	if (starts_with("-n", parsed_cmd[1]))
	{
		while (parsed_cmd[1][i] == 'n')
			i++;
		if (!parsed_cmd[1][i])
		{
			e_vars->n_line = 1;
			while (white_spaces(cmd[e_vars->i]))
				e_vars->i++;
			if (starts_with("-n",
					ft_substr(cmd, e_vars->i, ft_strlen(parsed_cmd[1]))))
			{
				e_vars->i += ft_strlen(parsed_cmd[1]);
				return ;
			}
		}
	}
}
