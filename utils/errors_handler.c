/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:29:38 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/04/25 18:15:01 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	bash_syntax_error(t_shell *s, int err)
{
	if (!err)
		ft_putstr_fd("bash: io_file error\n", 2);
	else if (err == 2)
		ft_putstr_fd("bash: syntax error '|'\n", 2);
	s->input_error = 1;
	s->cmdretval = 2;
	return (0);
}

void	error_cmd_not_found(t_shell *s, char *cmd)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(" command not found\n", 2);
	s->cmdnotfound = 1;
	s->input_error = 1;
	s->cmdretval = 127;
}

void	bash_error_w_filename(t_shell *s, char *file)
{
	ft_putstr_fd("bash", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	s->input_error = 1;
	s->cmdretval = errno;
}

void	quotes_error(t_shell *s)
{
	ft_putstr_fd("quotes error\n", 2);
	s->input_error = 1;
	s->cmdretval = 1;
	return ;
}
