/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:48:19 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/04/05 14:28:34 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	valid_export(char *str, int i)
{
	if (!ft_isalpha(str[i]) && !(str[i] == '_'))
		return (0);
	return (1);
}

// here we store the value the user gave us for the variavle 
// -->| i is where wefound '=' \\line:33

// here we check if the var already exist in the env_vars \\line:37

// update the var value line : 42
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

/* prepares the variables for the expoort function 
-->or the change_var_value function if the variable already exists */

// we split the command export to multiple words and store it in 2d_arr
//line:77

// we check if the characters in the variabl are valid "dont start with number"
//line:83

//look for '=' in the var_name so we can return everything before it as variable
//line:85

// we save the var name we only take first part |var_name="fgdfgdf"| 'var_name'
//line:87

// 'i' is the place where we found '='
//line:93
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

// reproduces the "export" command only without args

//prints the name of the env without '='
//line:117
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
