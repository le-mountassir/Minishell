/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:48:46 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/17 14:10:08 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* changes the value of the variable pointed to by *var to the value pointed by *value */

int	change_var_value(t_shell *shell, char *env_var, char *value)
{
	int	i;

	i = 0;
	while (shell->our_env[i] && !(starts_with(env_var, shell->our_env[i])))
		i++;
	if (!shell->our_env[i])
		return (0);
	free(shell->our_env[i]);
	shell->our_env[i] = malloc(
			sizeof(char) * (ft_strlen(env_var) + ft_strlen(value) + 2));
	if (!shell->our_env[i])
		exit(1);
	ft_strlcpy(shell->our_env[i],env_var, ft_strlen(env_var) + 1);
	ft_strlcat(shell->our_env[i], "=", ft_strlen(shell->our_env[i]) + 2);
	ft_strlcat(shell->our_env[i], value,
		ft_strlen(shell->our_env[i]) + ft_strlen(value) + 1);
	return (1);
}

char	*get_val(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[j] && ((str[j] >= 9 && str[j] <= 13) || str[j] == ' '))
		j++;
	i = j;
	while (str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, j, i));
}

/* returns a string containing the value of the environment variable */

char	*get_envar_value(t_shell *shell, char *str)
{
	int		i;
	int		j;
	char	*var;

	i = -1;
	while (shell->our_env[++i])
	{
		j = 0;
		while (shell->our_env[i][j] && shell->our_env[i][j] != '=')
			j++;
		var = ft_substr(shell->our_env[i], 0, j);
		if (!var)
			exit(1);
		if (starts_with(str, var) && (int)ft_strlen(str) == j)
		{
			free(var);
			var = ft_substr(shell->our_env[i], j + 1, ft_strlen(shell->our_env[i]) - j);
			if (!var)
				exit(1);
			return (var);
		}
		free(var);
	}
	return (NULL);
}
