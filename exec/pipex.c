/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:58:38 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/02/27 18:03:26 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

void	out_process(char *cmd, char **env)
{
	int		fd;
	char	*path;
	char	**str;

	str = ft_split(cmd, ' ');
	fd = 0;
	path = find_path(str[0]);

	if (!fork())
		execve(path, str, env);

	waitpid(-1, 0 ,0);
}

static void	do_pipe(char *cmd, char **env)
{
	int		fds[2];
	int		pid;
	char	*path;
	char	**str;
		
	str = ft_split(cmd, ' ');
	
	pipe(fds);

	pid = fork();

	if (pid == 0)
	{
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		path = find_path(str[0]);
		execve(path, str, env);
	}
	else
	{
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO); 
	}
	waitpid(-1, 0, 0);
}

int	pipex(int num_of_cmds, char **commands, char **env)
{
	int		i;

	i = 0;
	while (i < num_of_cmds)
		do_pipe(commands[i++], env);
	out_process(commands[num_of_cmds], env);
	return (0);
}
