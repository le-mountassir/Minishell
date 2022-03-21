/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:00:48 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/21 11:15:05 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// we check if the command is executable
// returnb 0 if the command exict wjich means its executable
int	not_executable_cmd(t_shell *s, char *cmd)
{
	char		*exec;
	int j = 0;

	if (starts_with("export", cmd))
		return (0);
	if (!cmd || !(access(cmd, X_OK)))
		return (0);
	if (!s->path)
	{
		error_cmd_not_found(s, cmd);
		return (1);
	}
	while (s->path[j])
	{
		exec = ft_join(s->path[j], cmd);
		if (!exec)
			exit(1);
		if (!(access(exec, X_OK)))
		{
			free(exec);
			return (0);
		}
		free(exec);
		j++;
	}
	error_cmd_not_found(s, cmd);
	return (1);
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