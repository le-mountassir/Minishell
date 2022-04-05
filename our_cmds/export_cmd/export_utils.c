/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:48:11 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/26 18:11:50 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* returns the line at which the new environment variable should be placed */

// when the new_var is sorted we return the index 
// -->of the place where we should put it
//line:26
static int	new_var_placement(t_shell *shell, char *new_var)
{
	int	i;

	i = 0;
	while (shell->our_env[i])
	{
		if (is_sorted(new_var, shell->our_env[i]))
			return (i);
		i++;
	}
	return (i);
}

static void	alphalloc(char **tmp, char *str, int j, int *alpha)
{
	*alpha = -1;
	tmp[j] = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!tmp[j])
		exit(1);
	ft_strlcpy(tmp[j], str, ft_strlen(str) + 1);
}

/* iterates through the environment table and assigns the right values */

static void	assign(t_shell *shell, char *new_var, char **tmp)
{
	int	i;
	int	j;
	int	alpha;

	i = 0;
	j = 0;
	alpha = new_var_placement(shell, new_var);
	while (shell->our_env[i])
	{
		if (i != alpha)
		{
			tmp[j] = malloc(sizeof(char) * (ft_strlen(shell->our_env[i]) + 1));
			if (!tmp[j])
				exit(1);
			ft_strlcpy(tmp[j], shell->our_env[i],
				ft_strlen(shell->our_env[i]) + 1);
			i++;
		}
		else
			alphalloc(tmp, new_var, j, &alpha);
		j++;
	}
	if (alpha != -1)
		alphalloc(tmp, new_var, j, &alpha);
}

// here we allocat a new env_vars bcs we want to add a new one
// we allocat a tmp_env_vars + 1 new var + NULL
//line:82
void	assign_new_var(t_shell *shell, char *arg)
{
	int		i;
	char	**tmp;

	i = td_arr_len(shell->our_env);
	tmp = malloc(sizeof(char *) * (i + 2));
	if (!tmp)
		exit(1);
	assign(shell, arg, tmp);
	tmp[i + 1] = 0;
	free_arr(shell->our_env);
	shell->our_env = malloc(sizeof(char *) * (i + 2));
	shell->our_env[i + 1] = 0;
	while (i >= 0)
	{
		shell->our_env[i] = ft_strdup(tmp[i]);
		if (!shell->our_env[i])
			exit(1);
		i--;
	}
	free_arr(tmp);
}

// the enset cmd remove the var u want from the envirement vars