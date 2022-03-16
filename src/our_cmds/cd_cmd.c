/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:31:53 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/14 18:02:34 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
		perror("bash: cd");
		shell->cmdretval = errno;
	}
	free(pwd);
}


static void	en_var_path(t_shell *shell, char *option)
{
	char	*var_name;
	char	*path;

	var_name = ft_substr(option, 1, ft_strlen(option)); // here we skip the '$' so we can get the env_var name
	if (!var_name)
		exit(1);
	path = get_envar_value(shell, var_name);
	go_to_folder(shell, path); // then we call ge_to with the path we got from the env_var
	free(var_name);
	if (path)
		free(path);
}

// goes to the home folder, example: "cd" without options
static void	back_to_home(t_shell *shell, char *home_dir)
{
	char	*pwd;

	pwd = getcwd(NULL, 0); // returns a str containing the current working dir we store it in pwd
	if (!pwd)
		exit(1);
	
	if (!chdir(home_dir)) // the chdir function change the current dir to the HOME_dir. On success, zero is returned.
	{
		change_var_value(shell, "OLDPWD", pwd); // here we change the oldpwd in en_var to the one we stored in "pwd"
		pwd = getcwd(NULL, 0); // update pwd with the new path
		if (!pwd)
			exit(1);
		if (!change_var_value(shell, "PWD", pwd)) // change the value of the new path in the en_var
			exit (1);
	}
	else
	{
		perror("cd command failed");
		shell->cmdretval = errno;
	}
	free(pwd);
}

/* redirects to the right functions */
static void	cd_redirection(t_shell *shell, char *cmd, char *option, char *home_dir)
{
	if (starts_with("cd", cmd) && ft_strlen(cmd) == 2)
	{
		if (!option) // here we check if the cd option is NULL if yes we cd to HOME
			back_to_home(shell, home_dir);
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

void	cd_cmd(t_shell *shell)
{
	char	*home_dir;
	char	**tab;

	if (shell->num_of_cmds > 1)
		return ;
	home_dir = get_envar_value(shell, "HOME");
	if (!home_dir)
	{
		perror("cd: home directory not found\n");
		exit(1);
	}
	tab = ft_split(shell->cmd[0], ' ');
	if (!tab)
		exit(1);
	cd_redirection(shell, tab[0], tab[1], home_dir);
	free(home_dir);
	free_arr(tab);
}
