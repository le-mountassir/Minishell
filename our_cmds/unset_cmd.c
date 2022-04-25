/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:48:38 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/04/25 18:17:27 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	not_env_var(t_shell *shell, char *var)
{
	int	i;

	i = -1;
	while (shell->our_env[++i])
	{
		if (starts_with(var, shell->our_env[i]))
			return (0);
	}
	return (1);
}

static void	refill_our_env(t_shell *shell, char *str, char **tmp)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (shell->our_env[++i])
	{
		if (!starts_with(str, shell->our_env[i]))
		{
			tmp[++j] = ft_strdup(shell->our_env[i]);
			if (!tmp[j])
				exit(1);
		}
	}
	tmp[++j] = 0;
	free_arr(shell->our_env);
	shell->our_env = malloc(sizeof(char *) * 1000);
	i = -1;
	while (tmp[++i] && i < j)
	{
		shell->our_env[i] = ft_strdup(tmp[i]);
		if (!shell->our_env[i])
			exit(1);
	}
	shell->our_env[i] = NULL;
}

void	unset_cmd(t_shell *shell, char **cmd)
{
	int		i;
	int		env_size;
	char	**tmp;

	i = 0;
	env_size = td_arr_len(shell->our_env);
	tmp = malloc(sizeof(char *) * env_size);
	if (!tmp)
		return ;
	while (cmd[++i])
	{
		check_quotes(shell, cmd, i);
		if (not_env_var(shell, cmd[i]))
			break ;
		refill_our_env(shell, cmd[i], tmp);
	}
	free_arr(tmp);
}
