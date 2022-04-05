/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:28:13 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/04/03 18:24:18 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	if (sig == SIGINT && g_cld_proc == 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT && g_cld_proc == 0)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static int	clean_input(t_shell *shell, char **v, int i)
{
	v = NULL;
	i = 0;
	if (shell->input_error)
		return (0);
	if (!shell->cmd[0])
		return (0);
	while (shell->cmd[0][i]
		&& (white_spaces(shell->cmd[0][i]) || shell->cmd[0][i] == '\n'))
	i++;
	if (shell->cmd[0][i] == '\0')
	{
		free(shell->cmd[0]);
		return (0);
	}
	return (1);
}

// signal(SIGQUIT, SIG_IGN); // ignores the SIGINT with SIG_IGN
int	main(int c, char **v, char **env)
{
	t_shell	shell;
	char	*rl_return;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	init_structure(&shell, env);
	shell_levels(&shell);
	while (1)
	{
		rl_return = readline("Minishell_$:");
		if (!rl_return)
			exit (1);
		if (!rl_return[0])
		{
			free(rl_return);
			continue ;
		}
		add_history(rl_return);
		reinit_structure(&shell);
		split_commands(&shell, rl_return);
		if (clean_input(&shell, v, c))
			start_shell(&shell);
	}
	free_struct(&shell);
	return (0);
}
