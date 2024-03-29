/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:00:48 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/04/25 18:15:29 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_executable(t_shell *s, char *cmd)
{
	char	*exec;
	int		j;

	j = 0;
	while (s->path[j])
	{
		exec = ft_join(s->path[j], cmd);
		if (!exec)
			exit(1);
		if (!(access(exec, X_OK)))
		{
			free(exec);
			return (1);
		}
		free(exec);
		j++;
	}
	return (0);
}

int	not_executable_cmd(t_shell *s, char *cmd)
{
	if (!ft_strcmp("exit", cmd) || !ft_strcmp("unset", cmd)
		|| !ft_strcmp("export", cmd) || !ft_strcmp("env", cmd)
		|| !ft_strcmp("pwd", cmd) || !ft_strcmp("echo", cmd))
		return (0);
	if ((!cmd || !(access(cmd, X_OK))) && !s->var)
		return (0);
	if (!s->path)
	{
		error_cmd_not_found(s, cmd);
		return (1);
	}
	if (is_executable(s, cmd))
		return (0);
	error_cmd_not_found(s, cmd);
	return (1);
}

int	is_quote(char *s, int i, int quote)
{
	return (s[i] == quote && s[i - 1] != '\\');
}

int	go_next_quote(t_shell *sh, char *cmd, int i, int quote)
{
	i += 1;
	while (cmd[i] && !is_quote(cmd, i, quote))
		i++;
	if (!cmd[i])
		quotes_error(sh);
	return (i);
}

void	make_our_env(t_shell *shell)
{
	shell->our_env = malloc(sizeof(char *) * 5);
	shell->our_env[0] = ft_strjoin("PATH=", _PATH_STDPATH);
	shell->our_env[1] = ft_strjoin("PWD=", getcwd(NULL, 0));
	shell->our_env[2] = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
	shell->our_env[3] = ft_strjoin("SHLVL=", "1");
	shell->our_env[4] = NULL;
}
