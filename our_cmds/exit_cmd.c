/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:32:07 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/21 12:41:19 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exit_status(t_shell *shell, char **cmd)
{
	if (ft_isnumber(cmd[1]))
	{
		printf("exit\n");
		free_arr(shell->cmd);
		exit(ft_atoi(cmd[1]));
	}
	else
	{
		printf("exit: %s: argument must be a number\n", cmd[1]);
		free_arr(shell->cmd);
		exit(1);
	}
}

/* checks if the command "exit" was put in the s, and exits if that's the case */

void	exit_cmd(t_shell *s)
{
	char	**cmd;

	if (!ft_strcmp("exit", s->cmd[0])) // if there is only exit without args or exit status we just exit
	{
		free_arr(s->cmd);
		exit(0);
	}
	cmd = ft_split(s->cmd[0], ' ');
	if (!cmd)
		exit(1);

	if (td_arr_len(cmd) == 2)
		exit_status(s, cmd);
	else if (td_arr_len(cmd) > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		free_arr(s->cmd);
		free_arr(cmd);
		exit(1);
	}	
}
