/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:25:06 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/02/23 17:02:45 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

void	exec_cmd(t_vars *unit, char **cmd, char **env)
{
	char **command;
	char *path;
	int i = 0;
	
	command = ft_split(unit->rl_return, ' '); // we split the user input  [0 = ls] [1 = -la] ...
	if (!command[0])
		return ;
	
	if (command[0][0] == '$') // if the first char in the user input is a '$' it mean that the input is envirement variable related
		env_var(command);

	// here we check if the first char is '/' it means that the user gave us a path of the cmd he wants to execute
	if (command[0][0] == '/') 
		path = command[0];
	// if there is no '/' we compare the user's 1st argument with our homemade commands if it match's we execute it if not we call find_path
	else if (!(cmp_with_homemade(command, unit)))
		path = find_path(command[0]);
		
	if(!access(path,R_OK))
	{
		int fok = fork();
		if(fok == 0)
			execve(path, command, env);
		waitpid(-1, 0, 0);
	}
}