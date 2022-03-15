/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:29:52 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/12 15:12:20 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free(char *s)
{
	if (s)
		free(s);
	s = NULL;
}

void	free_arr(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	if (array)
		free(array);
	array = NULL;
}

void	free_struct(t_shell *s)
{
	free_arr(s->cmd);
	free_arr(s->path);
	free_arr(s->cmd_with_args);
	free_arr(s->our_env);
	if (s->file.stopword)
		free(s->file.stopword);
	if (s->file.input_fd)
		free(s->file.input_fd);
	if (s->file.outfile)
		free(s->file.outfile);
	// rl_clear_history();
}

int	ft_exit(t_shell *shell, char *err)
{
	perror(err);
	free_struct(shell);
	exit(0);
}
