/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:28:50 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/20 14:33:30 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// katreturn lblasa fin 2strs tkhalfo we use it to check if s2 starts with s1  and return where s1 stopped in s2
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

// replace str in dst with src
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

void	swap_file(t_shell *s, char **file, char **arg, int f_name)
{
	int	fd;

	if (*file)
	{
		fd = open(*file, O_CREAT | O_RDWR, 0777);
		if (fd < 0)
			ft_exit(s, "File not created");
		free(*file);
	}
	*file = ft_strdup(arg[f_name]);
	if (!*file)
		exit(1);
}

int	dbquote_check(char *cmd, int i, int quote)
{
	if ((cmd[i] == '"' || cmd[i] == '\\') && cmd[i - 1] == '\\')
		return (1);
	else if(cmd[i] == '\\' && !(cmd[i+1] == '"' || cmd[i+1] == '\\'))
		return (1);
	else if (!(cmd[i] == quote || cmd[i] == '\\'))
		return (1);
	return (0);
}

