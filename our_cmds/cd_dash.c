/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_dash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:32:49 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/04/03 15:11:28 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* handles the directory changes */

static void	change_dir(t_shell *shell, char *new_pwd)
{
	char	old_pwd[9999];

	getcwd(old_pwd, 9999);
	if (!chdir(new_pwd))
	{
		if (!change_var_value(shell, "OLDPWD", old_pwd))
			return (ft_putstr_fd("cd :OLDPWD not set\n", 2));
		if (!change_var_value(shell, "PWD", new_pwd))
			return (ft_putstr_fd("cd :PWD not set\n", 2));
	}
	else
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
}

// cd -
void	dash_handler(t_shell *shell)
{
	char	*old_pwd;

	old_pwd = get_envar_value(shell, "OLDPWD");
	change_dir(shell, old_pwd);
	free(old_pwd);
}
