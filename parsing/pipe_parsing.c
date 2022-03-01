/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:09:12 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/01 14:09:54 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

void	pipes_parsing(t_vars *unit)
{
	int i =0;
	char **commands;
	commands = ft_split(unit->rl_return, '|');
	
	while (commands[i])
	{
		commands[i] = rm_space(commands[i]);
		commands[i] = ft_strtrim(commands[i], "\"\'");
		i++;
	}
	
	if (!fork())
		pipex(i-1, commands, unit->env);
	waitpid(-1, 0 ,0);
}