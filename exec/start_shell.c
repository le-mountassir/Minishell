/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:32:00 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/21 17:35:16 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	get_cmd_retvalue(t_shell *s, int status)
{
	if (WIFEXITED(status))
		s->cmdretval = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		s->cmdretval = WTERMSIG(status) + 128;
	else if (WIFSTOPPED(status))
		s->cmdretval = WSTOPSIG(status);
}

static void	check_homemade_cmds(t_shell *shell)
{
	// signal(SIGQUIT, handle_sigquit);
	
	cd_cmd(shell); // checks if the command is cd if yes it execute it
	if (starts_with("unset ", shell->cmd[0])) // checks if there is and arg after unset if yes it calls unset_cmd
		unset_cmd(shell);
	else if (starts_with("export ", shell->cmd[0])) // checks if there is and arg after export if yes it calls unset_cmd
		export_cmd(shell);
	else if (starts_with("exit", shell->cmd[0]))
		exit_cmd(shell); // checks if the command is exit if yes it execute it
	else
		return ;
	shell->home_made_cmd = 1;
}

/* increment the SHLVL environment variable by*/
//SHLVL m3natha layers dial shell shell fo9 shell 
// zdna b 1 7itach shell dialna ghnft7oh fo9 nother shell
void	shell_levels(t_shell *shell)
{
	int		lvl;
	char	*tmp;

	tmp = get_envar_value(shell, "SHLVL");
	if (!tmp)
		exit(1);
	lvl = ft_atoi(tmp);
	free(tmp);
	lvl++;
	tmp = ft_itoa(lvl);
	change_var_value(shell, "SHLVL", tmp);
	free(tmp);
}

void	start_shell(t_shell *s)
{
	int	i;
	int	pid;
	int	status;
	
	i = -1;
	if (s->num_of_cmds <= 1)
		check_homemade_cmds(s);
	if (s->home_made_cmd) // we check if the home_made_cmd is true if yes it means that there was only 1 command and we executed it i previous if statement
		return (free_arr(s->cmd));
	execution(s);
	free_arr(s->cmd);
	while (++i < s->num_of_cmds)
	{
		pid = wait(&status);
		if (pid == cld_proc)
			get_cmd_retvalue(s, status);
	}
	cld_proc = 0;
}
