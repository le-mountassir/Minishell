/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:31:53 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/25 15:38:46 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* goes to a specific directory, example: "cd some-directory" */

static void	go_to_folder(t_shell *shell, char *folder_p)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!chdir(folder_p))
	{
		change_var_value(shell, "OLDPWD", pwd);
		free(pwd);
		pwd = getcwd(NULL, 0);
		change_var_value(shell, "PWD", pwd);
	}
	else
	{
		ft_putstr_fd("bash: cd", 2);
		shell->cmdretval = errno;
	}
	free(pwd);
}

// here we skip the '$' so we can get the env_var name using substr
//line:44
static void	en_var_path(t_shell *shell, char *option)
{
	char	*var_name;
	char	*path;

	var_name = ft_substr(option, 1, ft_strlen(option));
	if (!var_name)
		exit(1);
	path = get_envar_value(shell, var_name);
	go_to_folder(shell, path);
	free(var_name);
	if (path)
		free(path);
}

// goes to the home folder, example: "cd" without options
static void	back_to_home(t_shell *shell, char *home_dir)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		exit(1);
	if (!chdir(home_dir))
	{
		change_var_value(shell, "OLDPWD", pwd);
		pwd = getcwd(NULL, 0);
		if (!pwd)
			exit(1);
		if (!change_var_value(shell, "PWD", pwd))
			exit (1);
	}
	else
	{
		ft_putstr_fd("cd command failed\n", 2);
		shell->cmdretval = errno;
	}
	free(pwd);
}

/* redirects to the right functions */
static void	cd_redirection(t_shell *shell, char *cmd,
	char *option, char *home_dir)
{
	if (starts_with("cd", cmd) && ft_strlen(cmd) == 2)
	{
		if (!option)
		{
			if (!home_dir)
				return (ft_putstr_fd("cd: home directory not found\n", 2));
			back_to_home(shell, home_dir);
		}
		else
		{
			if (starts_with("-", option) && ft_strlen(option) == 1)
				tilde_handler(shell);
			else if (starts_with("$", option))
				en_var_path(shell, option);
			else
				go_to_folder(shell, option);
		}
		shell->home_made_cmd = 1;
	}
}

/* calls the redirection function and frees everything */
// we cant cd when there is a pipe so we skip cd
//line:108
void	cd_cmd(t_shell *shell)
{
	char	*home_dir;
	char	**tab;

	if (shell->num_of_cmds > 1)
		return ;
	home_dir = get_envar_value(shell, "HOME");
	tab = ft_split(shell->cmd[0], ' ');
	if (!tab)
		exit(1);
	cd_redirection(shell, tab[0], tab[1], home_dir);
	free(home_dir);
	free_arr(tab);
}
