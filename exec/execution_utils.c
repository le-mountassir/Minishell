/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:30:37 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/04/03 14:30:10 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// if the user gave us a path we will execute it here line:24
// --> and no need to join the cmd with the PATH.

// if he gave us cmd we loop through the paths line:26/34
// -->and join them with the cmd and exec.
void	exec_cmd(t_shell *shell, int j)
{
	char	*cmd;

	if (shell->cmd_with_args[0] && !shell->input_error)
		execve(shell->cmd_with_args[0], shell->cmd_with_args, shell->our_env);
	while (!shell->input_error && shell->cmd_with_args[0] && shell->path[++j])
	{
		cmd = ft_join(shell->path[j], shell->cmd_with_args[0]);
		if (!cmd)
			exit(1);
		execve(cmd, shell->cmd_with_args, shell->our_env);
		free(cmd);
	}
}

int	home_made(t_shell *shell, int cmd_id)
{
	int		i;
	char	**new_cmd;
	char	pwd[9999];

	new_cmd = ft_split(shell->cmd[cmd_id], ' ');
	i = 0;
	if (starts_with("exit", shell->cmd[cmd_id])
		|| starts_with("unset", shell->cmd[cmd_id]))
		exit(1);
	if (starts_with("env", shell->cmd[cmd_id]))
		while (shell->our_env[i])
			printf("%s\n", shell->our_env[i++]);
	else if (!ft_strcmp("export", new_cmd[0]))
		display_export(shell);
	else if (starts_with("echo", shell->cmd[cmd_id]))
		echo_cmd(shell, shell->cmd_with_args, shell->cmd[cmd_id]);
	else if (starts_with("pwd", shell->cmd[cmd_id]))
	{
		getcwd(pwd, 9999);
		printf("%s\n", pwd);
	}
	else
		return (0);
	free_arr(new_cmd);
	return (1);
}
