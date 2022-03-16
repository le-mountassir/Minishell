/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:33:11 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/14 15:53:59 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

int	g_proc;

typedef struct redirection
{
	int		here_doc; // checks if there is a heredoc
	int		input; // checks if there is an input file
	char	*stopword; // heredoc stop word
	char	*input_fd; // '<' input file
	char	*outfile; // '>>' '>' output file
	int		tmpin;
	int		tmpout;
	int		tmpfd;
	int		fdin;
	int		fdout;
	int		append_f;
	int		over_write;
	int		more;
}				t_redir;

typedef struct shell_vars
{
	char	**our_env;
	char	**cmd; //2d arr containing the user input splited into commands
	char	**cmd_with_args; // we store the cmd after we splited it with its args
	int		pipe_fd[2]; // pipe
	int		*pipe_two;
	char	**path;
	int		error_skip; // 1 if there was an error
	int		num_of_cmds; // number of cmds
	int		home_made_cmd;
	int		single_qts;
	int		double_qts;
	int		cmdretval; // store last cmd return value
	int		cmdnotfound;
	int		syntax_error;
	int		quotes;
	int		no_path;
	t_redir	file; // struct containing vars for redirection
}				t_shell;

#endif
