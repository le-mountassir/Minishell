/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:48:19 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/14 18:35:23 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int	valid_export(char *str, int i)
{
	int		start;
	char	*s;

	if (!ft_strchr(str, '='))
		return (0);
	if (!ft_isalpha(str[i]))
	{
		printf("not a valid character\n");
		return (0);
	}
	return (1);
}

static void	set_value_or_newvar(t_shell *shell, char *arg, char *var_name, int i)
{
	char	*newv;
	char	*value;

	value = ft_substr(arg, i + 1, ft_strlen(arg)); // here we store the value of the user gave us for the variavle | i is where we found '='
	if (!value)
		exit(1);
	newv = get_envar_value(shell, var_name); // here we check if the var already exist in the env_vars
	if (!newv) // if no we 
		expoort(shell, arg);
	else // if yes we just change the value of the existing with the value that the user gave us
	{
		if (!change_var_value(shell, var_name, value))
			exit(1);
	}
	free(newv);
	free(value);
}

/* prepares the variables for the expoort function ||or the change_var_value function if the variable already exists */

void	export_cmd(t_shell *shell)
{
	char	*var_name;
	char	**export_cmd;
	int 	i = 0;
	int 	j= 1;
	
	export_cmd = split_export_cmd(shell->cmd[0]); // we split the command export to multiple words and store it in 2d_arr
	while (!ft_strcmp(export_cmd[j], "export"))
		j++;
	while (export_cmd[j])
	{
		i = 0;
		if (valid_export(export_cmd[j], i)) // we check if the characters in the variabl are valid
		{
			while (export_cmd[j][i] && export_cmd[j][i] != '=') // we look for the '=' in the var_name so we can return everything before it, as variable
				i++;
			var_name = ft_substr(export_cmd[j], 0, i); // we save the var name we only take first part |var_name="fgdfgdf"| 'var_name'
			if (!var_name)
				exit(1);
			set_value_or_newvar(shell, export_cmd[j], var_name, i); // 'i' is the place where we found '='
			free(var_name);
		}
		else if (ft_strcmp("export", export_cmd[j]))
			printf("export: `%s': not a valid identifier\n", export_cmd[j]);
		j++;
	}
	free_arr(export_cmd);
}

/* reproduces the "export" command only without args*/

void	display_export(t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while (shell->our_env[i])
	{
		j = 0;
		printf("declare -x ");
		while (shell->our_env[i][j] != '=') //prints the name of the env without '='
		{
			printf("%c", shell->our_env[i][j]);
			j++;
		}
		printf("=\""); // prints '="' and skips the space in the env var 'j++'
		j++;
		while (shell->our_env[i][j]) // prints the rest
		{
			printf("%c", shell->our_env[i][j]);
			j++;
		}
		printf("\"\n"); // and close it with '"'
		i++;
	}
}