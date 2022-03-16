/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:32:00 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/14 13:33:55 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_redir(t_shell *s)
{
	if (s->file.stopword)
		ft_free(s->file.stopword);
	if (s->file.input_fd)
		ft_free(s->file.input_fd);
	if (s->file.outfile)
		ft_free(s->file.outfile);
}

static void	get_cmd_retvalue(t_shell *s, int status)
{
	if (WIFEXITED(status))
		s->cmdretval = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		s->cmdretval = WTERMSIG(status) + 128;
	else if (WIFSTOPPED(status))
		s->cmdretval = WSTOPSIG(status);
}

static void	close_pipe(t_shell *s)
{
	int	i;
	int	pid;
	int	status;

	i = -1;
	free_arr(s->cmd);
	while (++i < s->num_of_cmds)
	{
		pid = wait(&status);
		if (pid == g_proc)
			get_cmd_retvalue(s, status);
	}
	g_proc = 0;
}


static void	check_homemade_cmds(t_shell *shell)
{
	int i = 0;
	signal(SIGQUIT, handle_sigquit);
	
	exit_cmd(shell); // checks if the command is exit if yes it execute it
	cd_cmd(shell); // checks if the command is cd if yes it execute it
	
	if (starts_with("env", shell->cmd[0])) // checks if the command is env if yes it prints our_envirement
	{
		while (shell->our_env[i])
		{
			printf("%s\n", shell->our_env[i]);
			i++;
		}
	}
	else if (!ft_strcmp("export", shell->cmd[0])) // if the args are the same it displays the export 
		display_export(shell);
	else if (starts_with("unset ", shell->cmd[0])) // checks if there is and arg after unset if yes it calls unset_cmd
		unset_cmd(shell);
	else if (starts_with("export ", shell->cmd[0])) // checks if there is and arg after export if yes it calls unset_cmd
		export_cmd(shell);
	else
		return ;
	shell->home_made_cmd = 1;
}

void	start_shell(t_shell *s)
{
	if (s->num_of_cmds <= 1)
		check_homemade_cmds(s);
	if (s->home_made_cmd) // we check if the home_made_cmd is true if yes it means that there was only 1 command and we executed it i previous if statement
		return (free_arr(s->cmd));
	pipe_line(s);
	close_pipe(s);
}
