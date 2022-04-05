/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:31:53 by acmaghou          #+#    #+#             */
/*   Updated: 2022/04/05 14:29:03 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* goes to a specific directory, example: "cd some-directory" */

static void	go_to_folder(t_shell *shell, char *folder_p)
{
	char	pwd[9999];

	getcwd(pwd, 9999);
	if (!chdir(folder_p))
	{
		change_var_value(shell, "OLDPWD", pwd);
		getcwd(pwd, 9999);
		change_var_value(shell, "PWD", pwd);
	}
	else
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(folder_p, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		shell->cmdretval = errno;
	}
}

// here we skip the '$' so we can get the env_var name using substr
//line:44
static void	variable_to_path(t_shell *shell, char *option)
{
	char	*var_name;
	char	*path;

	var_name = ft_substr(option, 1, ft_strlen(option));
	if (!var_name)
		return ;
	path = get_envar_value(shell, var_name);
	go_to_folder(shell, path);
	free(var_name);
	if (path)
		free(path);
}

// goes to the home folder, example: "cd" without options
static void	back_to_home(t_shell *shell, char *home_dir)
{
	char	pwd[9999];

	getcwd(pwd, 9999);
	if (!chdir(home_dir))
	{
		change_var_value(shell, "OLDPWD", pwd);
		getcwd(pwd, 999);
		change_var_value(shell, "PWD", pwd);
	}
	else
	{
		ft_putstr_fd("cd command failed\n", 2);
		shell->cmdretval = errno;
	}
}

/* redirects to the right functions */
static void	cd_redirection(t_shell *shell, char *option, char *home_dir)
{
	if (!option)
	{
		if (!home_dir)
		{
			return (ft_putstr_fd("cd: home directory not found\n", 2));
			shell->cmdretval = errno;
		}
		back_to_home(shell, home_dir);
	}
	else
	{
		if (!ft_strcmp("-", option))
			dash_handler(shell);
		else if (starts_with("$", option))
			variable_to_path(shell, option);
		else
			go_to_folder(shell, option);
	}
	shell->home_made_cmd = 1;
}

/* calls the redirection function and frees everything */
// we cant cd when there is a pipe so we skip cd
//line:108
void	cd_cmd(t_shell *shell, char **cmd)
{
	char	*home_dir;

	if (!ft_strcmp("cd", cmd[0]))
	{
		if (cmd[1])
			check_quotes(shell, cmd, 1);
		home_dir = get_envar_value(shell, "HOME");
		cd_redirection(shell, cmd[1], home_dir);
		free(home_dir);
	}
}
