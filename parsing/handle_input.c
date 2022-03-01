/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 22:39:33 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/01 14:24:53 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

void	parse_one_cmd(t_vars *unit)
{
	int i;
	
	i = -1;
	unit->rl_return = rm_space(unit->rl_return);
	command = ft_split(unit->rl_return, ' '); // we split the user input  [0 = ls] [1 = -la] ...
	if (!command[0])
		return ;
	while(command[++i])
		command[i] = ft_strtrim(command[i], "\"\'");
	exec_cmd(unit, command);
	ft_free_td(command);
}

void	handle_rl_input(t_vars   *unit)
{
	int check = 1;
	int i = 0;
	char **command;

	// this while loop checks if there is a pipe so we can handle the input using pipex
	while (unit->rl_return[i])
	{
		if (unit->rl_return[i] == '|')
		{
			check = 0;
			pipes_parsing(unit);
			break ;
		}
		i++;
	}
	// if there is no pipe it means that there is only 1 command to handle
	if (check)
		parse_one_cmd(unit);
}