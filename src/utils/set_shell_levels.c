/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shell_levels.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:48:25 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/08 11:22:59 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// /* executes environment variable commands */

// void	dollar(t_shell *shell)
// {
// 	char	*tmp;

// 	tmp = ft_substr(shell->cmd[0], 1, ft_strlen(shell->cmd[0]));
// 	if (!tmp)
// 		exit(1);
// 	free(shell->cmd[0]);
// 	shell->cmd[0] = get_envar_value(shell,
// 			ft_substr(shell->cmd[0], 1, ft_strlen(shell->cmd[0])));
// 	if (!shell->cmd[0])
// 		exit(1);
// 	free(tmp);
// }

/* increment the SHLVL environment variable by*/
//SHLVL m3natha layers dial shell shell fo9 shell 
// zdna b 1 7itach shell dialna ghnft7oh fo9 nother shell
void	shell_levels(t_shell *shell)
{
	int		lvl;
	char	*tmp;

	tmp = get_envar_value(shell, "SHLVL");
	if (!tmp)
		exit(1);
	lvl = ft_atoi(tmp);
	free(tmp);
	lvl++;
	tmp = ft_itoa(lvl);
	change_var_value(shell, "SHLVL", tmp);
	free(tmp);
}
