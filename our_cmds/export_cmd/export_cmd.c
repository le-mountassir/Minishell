/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:48:19 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/04/25 18:16:40 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	valid_export(char *str, int i)
{
	if (!ft_isalpha(str[i]) && !(str[i] == '_'))
		return (0);
	return (1);
}

static void	set_value_or_newvar(t_shell *shell, char *arg,
	char *var_name, int i)
{
	char	*newv;
	char	*value;

	value = ft_substr(arg, i + 1, ft_strlen(arg));
	if (!value)
		exit(1);
	newv = get_envar_value(shell, var_name);
	if (!newv)
		assign_new_var(shell, arg);
	else
	{
		if (!change_var_value(shell, var_name, value))
			exit(1);
	}
	free(newv);
	free(value);
}

void	export_cmd(t_shell *shell)
{
	char	*var_name;
	char	**export_cmd;
	int		i;
	int		j;

	i = 0;
	j = 1;
	export_cmd = split_export_cmd(shell->cmd[0]);
	while (export_cmd[j])
	{
		i = 0;
		if (valid_export(export_cmd[j], i))
		{
			while (export_cmd[j][i] && export_cmd[j][i] != '=')
				i++;
			var_name = ft_substr(export_cmd[j], 0, i);
			set_value_or_newvar(shell, export_cmd[j], var_name, i);
			free(var_name);
		}
		else if (ft_strcmp("export", export_cmd[j]))
			printf("export: `%s': not a valid arg\n", export_cmd[j]);
		j++;
	}
	free_arr(export_cmd);
}

void	display_export(t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while (shell->our_env[i])
	{
		j = 0;
		printf("declare -x ");
		while (shell->our_env[i][j] != '=')
		{
			printf("%c", shell->our_env[i][j]);
			j++;
		}
		printf("=\"");
		j++;
		while (shell->our_env[i][j])
		{
			printf("%c", shell->our_env[i][j]);
			j++;
		}
		printf("\"\n");
		i++;
	}
}
