/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:48:32 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/06 14:40:06 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* returns the line at which the new environment variable should be placed */

int	alpharank(t_shell *shell, char *new_var)
{
	int	i;

	i = 0;
	while (shell->our_env[i])
	{
		if (is_sorted(new_var, shell->our_env[i])) // when the new_var is sorted we return the index of the place where we should put it
			return (i);
		i++;
	}
	return (i);
}

int	is_sorted(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] != '=' && s1[i] == s2[i])
		i++;
	if (s1[i] > s2[i])
		return (0);
	return (1);
}


/* returns 1 if the env table is alphabetically sorted, 0 if it isn't */

static int	sorted(t_shell *shell)
{
	int	i;

	i = 1;
	while (shell->our_env[i])
	{
		if (!is_sorted(shell->our_env[i - 1], shell->our_env[i]))
			return (0);
		i++;
	}
	return (1);
}

/* swap unsorted strings */

static void	swap_unsorted(t_shell *shell, int j)
{
	char	*tmp;

	tmp = ft_strdup(shell->our_env[j - 1]);
	if (!tmp)
		exit(1);
	free(shell->our_env[j - 1]);
	shell->our_env[j - 1] = ft_strdup(shell->our_env[j]);
	if (!shell->our_env[j - 1])
		exit(1);
	free(shell->our_env[j]);
	shell->our_env[j] = ft_strdup(tmp);
	if (!shell->our_env[j])
		exit(1);
	free(tmp);
}

/* alphabetically sorts the environ array */

void	sort_env(t_shell *shell)
{
	int		i;
	int		j;

	j = 0;
	i = td_arr_len(shell->our_env);
	while (!sorted(shell))
	{
		j = 1;
		while (j < i)
		{
			if (!is_sorted(shell->our_env[j - 1], shell->our_env[j]))
				swap_unsorted(shell, j);
			j++;
		}
	}
}
