/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:48:38 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/04/05 14:36:14 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// checks if there is an envirement_var with the name "*var"
// -->if not we return in unset
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

// here we skip the envirement_var that we want to unset 
// -->basexcaly we just dont copy it to the new envirement line 40/48
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

// /* mallocs the new environment table and calls the refill_our_env function */
// the command unset removes a specefic var from the envirement
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
