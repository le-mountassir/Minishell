/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:58:38 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/01 10:30:02 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

void	child_process(char *command, char **env)
{
	int		pid;
	int		fd[2];
	char	*path;
	char	**m_cmd;

	if (pipe(fd) == -1)
		return ;
	m_cmd = ft_split(command, ' ');
	path = find_path(m_cmd[0]);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execve(path, m_cmd, env);
		waitpid(pid, NULL, 0);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
}

int	pipex(int last_arg, char **commands, char **env)
{
	int i = 0;
	char **cmd;
	while (i < last_arg)
		child_process(commands[i++], env);

	if(!fork())
	{
		cmd = ft_split(commands[last_arg], ' ');
		execve(find_path(cmd[0]), cmd, env);
	}
	waitpid(-1, 0 ,0);
}