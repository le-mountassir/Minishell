/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:00:48 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/12 17:37:49 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	builtin_cmd(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp("exit", cmd) || !ft_strcmp("export", cmd)
		|| !ft_strcmp("unset", cmd) || !ft_strcmp("cd", cmd));
}

// we check if the command is executable
// returnb 0 if the command exict wjichj means its executable
int	not_executable_cmd(t_shell *s, char *cmd)
{
	char		*exec;
	int j = 0;
	
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


int	not_pipeable_cmd(t_shell *s)
{
	if (only_hrdoc_with_nocmd(s) || builtin_cmd(s->cmd_with_args[0])
		|| (!s->file.stopword && not_executable_cmd(s, s->cmd_with_args[0])))
	{
		free_arr(s->cmd_with_args);
		return (1);
	}
	return (0);
}