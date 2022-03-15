/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:29:38 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/15 10:24:34 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* 
 * unexpectedToken error displays when redirections (<,<<,>>,>)
 * are not followed by a valid file, exaple echo hello > | cat myfile;
 * or when the pipe is misplaced
 */

int	bash_error_unexpected_token(t_shell *s, int err)
{
	if (!err)
		ft_putstr_fd("-bash: syntax error `newline'\n", 2);
	else if (err == 2)
		ft_putstr_fd("-bash: syntax error `|'\n", 2);
	s->syntax_error = 1;
	s->cmdretval = 2;
	return (0);
}

/* 
 * it prints command not found' message
 * and updates the return value to 127
 */

void	error_cmd_not_found(t_shell *s, char *cmd)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(" command not found\n", 2);
	s->cmdnotfound = 1;
	s->input_error = 1;
	s->cmdretval = 127;
}

/* 
 * it reproduces the '-bash: Filename: error' message
 */

void	bash_error_w_filename(t_shell *s, char *file)
{
	ft_putstr_fd("bash", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	s->input_error = 1;
	s->cmdretval = errno;
}

/* error when doublequotes or singlequotes are not closed*/

void	quotes_error(t_shell *s)
{
	ft_putstr_fd("quotes error\n", 2);
	s->input_error = 1;
	s->cmdretval = 1;
	return ;
}
