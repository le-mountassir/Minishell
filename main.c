/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:28:13 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/14 18:06:34 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	checker(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->error_skip)
		return (0);
	if (!shell->cmd[0])
		return (0);
	while (shell->cmd[0][i]
		&& (white_spaces(shell->cmd[0][i]) || shell->cmd[0][i] == '\n'))
	i++;
	if (shell->cmd[0][i] == '\0')
	 	return (0);
	return (1);
}


int	main(int c, char **v, char **env)
{
	t_shell	shell;
	char	*rl_return;
	
	// signal(SIGINT, handle_sigint);
	// signal(SIGQUIT, handle_sigquit);
	if (c > 1)
		return (printf("no need for arguments\n"));
	init_structure(&shell, env);
	shell_levels(&shell); // increment the SHLVL env-variable
	while (1)
	{
		signal(SIGQUIT, SIG_IGN); // ignores the SIGINT with SIG_IGN
		rl_return = readline("Minishell_$:");
		if (!rl_return)
			exit(1);
		add_history(rl_return);
		reinit_structure(&shell); // we reinit the shell args after every command
		split_commands(&shell, rl_return); // save the splited input in **shell->cmd
		if (checker(&shell))
			start_shell(&shell);
	}
	free_struct(&shell);
	rl_clear_history();
	return (0);
}
