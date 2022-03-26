/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tilde.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:32:49 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/24 13:37:24 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* handles the directory changes */

static void	change_dir(t_shell *shell, char *old_pwd, char *new_pwd)
{
	if (!chdir(new_pwd))
	{
		if (get_envar_value(shell, "OLDPWD"))
			change_var_value(shell, "OLDPWD", old_pwd);
		if (!change_var_value(shell, "PWD", new_pwd))
			exit(1);
	}
	else
		ft_putstr_fd("'cd -' error\n", 2);
}

// cd -
void	tilde_handler(t_shell *shell)
{
	char	*cur_pwd;
	char	*old_pwd;

	cur_pwd = getcwd(NULL, 0);
	old_pwd = get_envar_value(shell, "OLDPWD");
	if (!old_pwd)
		ft_putstr_fd("cd : OLDPWD not found\n", 2);
	change_dir(shell, cur_pwd, old_pwd);
}
