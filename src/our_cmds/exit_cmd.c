/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:32:07 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/14 13:44:58 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	tabtwo(t_shell *shell, char **cmd)
{
	if (ft_strlen(cmd[1]) < 20 && ft_isnumber(cmd[1]))
	{
		printf("exit\n");
		free_arr(shell->cmd);
		exit(ft_atoi(cmd[1]));
	}
	else
	{
		printf("exit\n");
		printf("bash: exit: %s: numeric argument required\n", cmd[1]);
		free_arr(shell->cmd);
		exit(1);
	}
}

/* checks if the command "exit" was put in the s, and exits if that's the case */

void	exit_cmd(t_shell *s)
{
	char	**cmd;

	if (!starts_with("exit", s->cmd[0]))
		return ;
	if (!ft_strcmp("exit", s->cmd[0]))
	{
		free_arr(s->cmd);
		exit(0);
	}
	cmd = ft_split(s->cmd[0], ' ');
	if (!cmd)
		exit(1);

	if (td_arr_len(cmd) == 2)
		tabtwo(s, cmd);
	else if (td_arr_len(cmd) > 2)
	{
		write(2, "bash: exit: too many arguments\n", 31);
		free_arr(s->cmd);
		free_arr(cmd);
		s->home_made_cmd = 1;
		exit(1);
	}	
}
