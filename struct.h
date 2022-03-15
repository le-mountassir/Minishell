/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:33:11 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/15 17:07:44 by ahel-mou         ###   ########.fr       */
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
	int		tmpfd;
	int		fdin;
	int		fdout;
	int		append_f; // append output to the file '>>'
	int		over_write; // over write to a file '>'
}				t_redir;

typedef struct shell_vars
{
	char	**our_env; // our shell envirement
	char	**cmd; //2d arr containing the user input splited into commands
	int		num_of_cmds; // number of cmds
	char	**cmd_with_args; // we store the cmd after we splited it with its args
	int		*pipe_two;
	char	**path;
	int		home_made_cmd;
	int		single_qts; // checks if there is a signle quote '\''
	int		double_qts; // checks if there is a double quote '"'
	int		cmdretval; // store last cmd return value
	int		cmdnotfound;
	int		input_error; // 1 if there was an error
	int		syntax_error;
	t_redir	file; // struct containing vars for file redirection
}				t_shell;

#endif
