/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:48:38 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/18 15:58:40 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// checks if there is an envirement_var with the name "*var" if not we return in unset

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

/* iterate through the environment table and update the env_var with the new value */

static void	refill_our_env(t_shell *shell, char *str, char **tmp)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (shell->our_env[++i])
	{
		if (!starts_with(str, shell->our_env[i])) // here we skip the envirement_var that we want to unset basexcaly we just skip it 
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

/* mallocs the new environment table and calls the refill_our_env function */

static void	unset(t_shell *shell, char *str)
{
	int		i;
	char	**tmp;

	if (not_env_var(shell, str))
		return ;
	i = td_arr_len(shell->our_env);
	tmp = malloc(sizeof(char *) * i);
	if (!tmp)
		exit(1);
	refill_our_env(shell, str, tmp);
	free_arr(tmp);
}

// prepares the arguments for the unset function
// the command unset removes a specefic var from the envirement

void	unset_cmd(t_shell *shell)
{
	int		i;
	char	**str;

	i = 0;
	str = ft_split(shell->cmd[0], ' ');
	while (str[++i]) // i starts from 1 to skip the unset command
		unset(shell, str[i]);
	free_arr(str);
}
