/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 22:39:33 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/02/23 14:46:00 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

// void	ft_pipes(t_vars *unit)
// {
// 	char **commands;

// 	commands = ft_split(unit->rl_return, '|');
// }

void	handle_rl_input(t_vars   *unit)
{
	int check = 1;
	int i = 0;

	unit->rl_return = rm_space(unit);

	// this while loop checks if there is a pipe so we can handle the input using pipex
	while (unit->rl_return[i])
	{
		if (unit->rl_return[i] == '|')
		{
			// ft_pipes(unit);
			check = 0;
		}
		i++;
	}
	// if there is no pipe it means that there is only 1 command to handle
	if (check)
	{
		exec_cmd(unit, NULL, unit->env);
	}
}
