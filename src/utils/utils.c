/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:28:50 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/15 16:06:18 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


/* katreturn lblasa fin 2strs tkhalfo*/
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

void	swap_file(t_shell *s, char **file, char **arg, int i_plus)
{
	int	fd;

	if (*file)
	{
		fd = open(*file, O_CREAT | O_RDWR, 0644);
		if (fd < 0)
			ft_exit(s, "File not created");
		free(*file);
	}
	*file = ft_strdup(arg[i_plus]);
	if (!*file)
		exit(1);
}

/*
* doublequote or backslash
*/

static int	dbq_or_bs(char c)
{
	return (c == '"' || c == '\\');
}

int	dbquote_check(char *cmd, int i, int quote)
{
	if (dbq_or_bs(cmd[i]) && cmd[i - 1] == '\\')
		return (1);
	else if(cmd[i] == '\\' && !dbq_or_bs(cmd[i + 1]))
		return (1);
	else if (!(cmd[i] == quote || cmd[i] == '\\'))
		return (1);
	return (0);
}

int	is_quote(char *s, int i, int quote)
{
	return (s[i] == quote && s[i - 1] != '\\');
}
// return an index of the closing quote
int	go_next_quote(t_shell *sh, char *cmd, int i, int quote)
{
	i += 1; // here we increment i bcs its the index of the first quote
	while (cmd[i] && !is_quote(cmd, i, quote))
		i++;
	if (!cmd[i])
		quotes_error(sh);
	return (i);
}