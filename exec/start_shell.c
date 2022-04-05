/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:32:00 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/04/05 14:29:38 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* increment the SHLVL environment variable by*/
//SHLVL m3natha layers dial shell shell fo9 shell
// zdna b 1 7itach shell dialna ghnft7oh fo9 nother shell
void	shell_levels(t_shell *shell)
{
	int		lvl;
	char	*tmp;

	tmp = get_envar_value(shell, "SHLVL");
	if (!tmp)
		return ;
	lvl = ft_atoi(tmp);
	free(tmp);
	lvl++;
	tmp = ft_itoa(lvl);
	change_var_value(shell, "SHLVL", tmp);
	free(tmp);
}

// check the status that the child_p exited with
// and asign it to cmdretval
static void	get_child_exit_status(t_shell *s, int status)
{
	if (WIFEXITED(status))
		s->cmdretval = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		s->cmdretval = WTERMSIG(status) + 128;
	else if (WIFSTOPPED(status))
		s->cmdretval = WSTOPSIG(status);
}

//the vars i and j are just for norm in export_cmd we init them here
// j stats from 1 to skip the cmd and go to the args
static void	check_homemade_cmds(t_shell *shell)
{
	char	**cmd;

	cmd = ft_split(shell->cmd[0], ' ');
	if (!cmd)
		return ;
	if (cmd[0])
		check_quotes(shell, cmd, 0);
	cd_cmd(shell, cmd);
	if (!ft_strcmp("unset", cmd[0]))
		unset_cmd(shell, cmd);
	else if (!ft_strcmp("export", cmd[0])
		&& td_arr_len(cmd) > 1 && !found_redir(shell->cmd[0]))
		export_cmd(shell);
	else if (!ft_strcmp("exit", cmd[0]))
		exit_cmd(shell, cmd);
	else
	{
		free_arr(cmd);
		return ;
	}
	shell->home_made_cmd = 1;
	free_arr(cmd);
}

// we check if the home_made_cmd is true if yes it means that there was
//only 1 command and we executed it i previous if statement
void	start_shell(t_shell *s)
{
	int	i;
	int	pid;
	int	status;

	i = -1;
	if (s->num_of_cmds == 1)
		check_homemade_cmds(s);
	if (s->home_made_cmd)
		return (free_arr(s->cmd));
	execution(s);
	free_arr(s->cmd);
	while (++i < s->num_of_cmds)
	{
		pid = wait(&status);
		if (pid == g_cld_proc)
			get_child_exit_status(s, status);
	}
	g_cld_proc = 0;
}
