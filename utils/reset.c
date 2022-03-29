/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:28:55 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/26 10:52:17 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_redir(char **cmd, int i)
{
	if (cmd[i])
	{
		free(cmd[i]);
		cmd[i] = NULL;
	}
}

void	reset_shell(t_shell *s)
{
	s->input_error = 0;
	s->cmdnotfound = 0;
	s->file.input_fd = 0;
	s->file.outfile = 0;
	s->file.stopword = 0;
	s->file.over_write = 0;
	s->file.append_f = 0;
	s->file.input = 0;
	s->file.here_doc = 0;
}
