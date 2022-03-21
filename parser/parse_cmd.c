/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:31:38 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/21 16:00:32 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_output_file(t_shell *shell, char **cmd, int i, int file_idx)
{
	if (cmd[file_idx])
		swap_file(shell, &shell->file.outfile, cmd, file_idx);
	else
		return (bash_syntax_error(shell, 0));
	remove_redir(cmd, i);
	remove_redir(cmd, file_idx);
	while (cmd[++file_idx])
	{
		if (cmd[i])
			free(cmd[i]);
		cmd[i] = ft_strdup(cmd[file_idx]);
		if (!cmd[i])
			exit(1);
		i++;
	}
	if (cmd[i])
		remove_redir(cmd, i);
	cmd[i] = 0;
	while (i++ < file_idx)
		remove_redir(cmd, i - 1);
	return (1);
}

static int	get_input_file(t_shell *shell, char **cmd, int i, int fname)
{
	if (cmd[fname] && shell->file.input)
		swap_file(shell, &shell->file.input_fd, cmd, fname);
	else if (cmd[fname] && shell->file.here_doc)
		swap_file(shell, &shell->file.stopword, cmd, fname);
	else
		return (bash_syntax_error(shell, 0));
	remove_redir(cmd, i);
	remove_redir(cmd, fname);
	while (cmd[++fname])
	{
		if (cmd[i])
			free(cmd[i]);
		cmd[i] = ft_strdup(cmd[fname]); // here we replace the redir and its arg with whats left in cmd
		if (!cmd[i])
			exit(1);
		i++;
	}
	if (cmd[i])
		remove_redir(cmd, i);
	cmd[i] = 0;
	while (i++ < fname)
		remove_redir(cmd, i - 1);
	return (1);
}

static int	check_redir(t_shell *shell, char **cmd, int i, int redir)
{
	if (!ft_strcmp(cmd[i], ">"))
	{
		shell->file.over_write = 1;
		redir = get_output_file(shell, cmd, i, i + 1);
	}
	else if (!ft_strcmp(cmd[i], ">>"))
	{
		shell->file.append_f = 1;
		redir = get_output_file(shell, cmd, i, i + 1);
	}
	else if (!ft_strcmp(cmd[i], "<"))
	{
		shell->file.input = 1;
		redir = get_input_file(shell, cmd, i, i + 1);
	}		
	else if (!ft_strcmp(cmd[i], "<<"))
	{
		shell->file.here_doc = 1;
		redir = get_input_file(shell, cmd, i, i + 1);
	}
	return (redir);
}

char	**parse_cmd(t_shell *shell, int j)
{
	int		i;
	char	**arg;

	i = -1;
	arg = split_cmd_args(shell, shell->cmd[j], ' '); // splits one command in a 2d_arr with its arguments 

	if (!arg)
		exit(1);
	while (arg[++i])
	{
		check_quotes(shell, arg, i); //check if theres quotes and remove them
		// if there ar db_quote and there is a var between then it replaces the var with its value
		check_var_or_retval(shell, arg, i);
		if (check_redir(shell, arg, i, 0) && i >= 0)
			i--; // we decriment bcs if there is a redirection we remove it from the arg and replace it with the stuff after it
	}
	shell->single_qts = 0;
	return (arg);
}
