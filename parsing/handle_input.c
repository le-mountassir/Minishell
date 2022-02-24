/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 22:39:33 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/02/24 09:12:29 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

// void	pipes_parsing(t_vars *unit)
// {
// 	char **commands;

// ');
// // }// 	commands = ft_split(unit->rl_return, '|

void	handle_rl_input(t_vars   *unit)
{
	int check = 1;
	int i = 0;
	char **command;

	unit->rl_return = rm_space(unit);

	// this while loop checks if there is a pipe so we can handle the input using pipex
	while (unit->rl_return[i])
	{
		if (unit->rl_return[i] == '|')
		{
			// pipes_parsing(unit);
			check = 0;
		}
		i++;
	}
	// if there is no pipe it means that there is only 1 command to handle
	if (check)
	{
		command = ft_split(unit->rl_return, ' '); // we split the user input  [0 = ls] [1 = -la] ...
		if (!command[0])
			return ;
		exec_cmd(unit, command);
	}
}
