/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:28:50 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/04/25 18:15:35 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	starts_with(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (s1[i] == '\0')
		return (i + 1);
	return (0);
}

void	str_replace(char **dst, char *src)
{
	if (!src)
		return ;
	if (*dst)
		free(*dst);
	*dst = ft_strdup(src);
	if (!*dst)
		exit(1);
	free(src);
}

int	dbquote_check(char *cmd, int i, int quote)
{
	if ((cmd[i] == '"' || cmd[i] == '\\') && cmd[i - 1] == '\\')
		return (1);
	else if (cmd[i] == '\\' && !(cmd[i + 1] == '"' || cmd[i + 1] == '\\'))
		return (1);
	else if (!(cmd[i] == quote || cmd[i] == '\\'))
		return (1);
	return (0);
}

int	check_pipe_error(char *str, int i)
{
	int	tr;

	tr = 0;
	if ((str[i] == '|' && !str[i + 1])
		|| (str[i] == '|' && str[i + 1] == '|'))
		return (1);
	i += 1;
	while (str[i] && str[i] != '|')
	{
		if (!white_spaces(str[i]))
			tr = 1;
		i++;
	}
	if (tr)
		return (0);
	return (1);
}

int	found_redir(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
		if (cmd[i] == '>')
			return (1);
	return (0);
}
