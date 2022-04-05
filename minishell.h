/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:33:06 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/04/05 14:28:41 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include "readline/readline.h"
# include "readline/history.h"
# include <paths.h>

# define READ 0
# define WRITE 1

int	g_cld_proc;

typedef struct echo_vars
{
	char	*txt;
	char	*cmd;
	int		n_line;
	int		i;
	int		k;
	char	*tmp;
}			t_echo;

// checks if there is a heredoc
// checks if there is an input file
// heredoc stop word
// '<' input file
// '>>' '>' output file
// fd of the tmpfile for the heredoc
// file discriptor of the output file
// fd of the input file
// append output to the file '>>'
// over write to a file '>'
typedef struct redirection
{
	int		here_doc;
	int		input;
	char	*stopword;
	char	*input_fd;
	char	*outfile;
	int		tmpfd;
	int		fdout;
	int		fdin;
	int		append_f;
	int		over_write;
}				t_redir;

// our shell envirement
//2d arr containing the user input splited into commands
// number of cmds
// we store the cmd after we splited it with its args
// checks if there is a signle quote '\''
// checks if there is a double quote '"'
// store last cmd return value
//----->
// 1 if there was an error
// struct containing vars for file redirection t_redir
typedef struct shell_vars
{
	char	**our_env;
	char	**cmd;
	int		num_of_cmds;
	char	**cmd_with_args;
	int		pipe_two[2];
	char	**path;
	int		home_made_cmd;
	int		single_qts;
	int		double_qts;
	int		cmdretval;
	int		cmdnotfound;
	int		input_error;
	int		var;
	t_redir	file;
}				t_shell;

//---------------------------------------------------------parsing
// split usser input with pipes into multiple commands
int		split_commands(t_shell *shell, char *line);
// checks if there is a $var and replace it with its vaue 
// --> or if there is a $? last_retval
void	check_var_or_retval(t_shell *s, char **arg, int i);
// split a cmd with its args in a 2d_arr
char	**split_cmd_args(t_shell *sh, char *command, char c);
// split 1 cmd into a 2d_arr with its arguments using space
char	**parse_cmd(t_shell *s, int i);
void	check_dollar(t_shell *s, char **arg, int i);
void	check_quotes(t_shell *s, char **arg, int i);

//---------------------------------------------------Home made commands
void	exit_cmd(t_shell *shell, char **cmd);
void	cd_cmd(t_shell *shell, char **cmd);
void	dash_handler(t_shell *shell); // handle the 'cd -'
void	display_export(t_shell *shell);
void	unset_cmd(t_shell *shell, char **cmd);
void	export_cmd(t_shell *shell);
//split the command export into multipl words ||"cmd" "name"="args"|| ..
char	**split_export_cmd(char const *str);
int		is_dollar(char *s, int i);
char	*get_dollar_value(t_shell *s, char *str, int *j);
void	echo_cmd(t_shell *s, char **parsed_cmd, char *original_cmd);

//-----------------------------------------------------------exec
void	start_shell(t_shell *s); //pre_executing part
void	execution(t_shell *s); // execution
void	exec_cmd(t_shell *shell, int j);
// checks id there is only a heredoc without a cmd after it
int		only_hrdoc_with_nocmd(t_shell *s);
// checks if the command is executable
int		not_executable_cmd(t_shell *s, char *cmd);
int		home_made(t_shell *shell, int cmd_id);

void	checkfile_redir(t_shell *s);
void	get_fds(t_shell *s, int i, int *pipe_fd);
void	get_heredoc(t_shell *s); // heredoc 
void	fork_failed(t_shell *s);
void	close_fds(t_shell *s);

//--------------------------------------------------------- ENVIRONMENT utils
// change *var value with *value
int		change_var_value(t_shell *shell, char *var, char *value);
// returns the valus of the env variable
char	*get_envar_value(t_shell *shell, char *str);
void	enver(t_shell *shell);
void	assign_new_var(t_shell *shell, char *str);
char	*get_val(char *str);
void	sort_env(t_shell *shell);
int		is_sorted(char *s1, char *s2);
void	shell_levels(t_shell *shell);

//------------------------------------------------------------utils
void	init_structure(t_shell *s, char **env);
void	reinit_structure(t_shell *s);
int		go_next_quote(t_shell *sh, char *cmd, int i, int quotes);
char	**split_cmd_ags(t_shell *sh, char *command, char c);
int		dbquote_check(char *cmd, int i, int quote);
int		is_quote(char *s, int i, int quotes);
// replace the the redir and  file_name with whats left in the cmd 
// --> "< Makefile wc -l" ==> "wc -l"
void	remove_redir(char **s, int i);
// replace str in dst with src we use it to replace variable with the value 
// -->and remove quotes while parsing
void	str_replace(char **dst, char *src);
void	free_arr(char **array);
void	free_redir(t_shell *s);
int		starts_with(char *s1, char *s2);
int		valid_dbquote(char *s, int j, int Q);
int		not_doublequote(char *s, int j);
void	reset_shell(t_shell *s);
void	free_struct(t_shell *s);
void	ft_free(char *s);
void	switch_pipe(t_shell *shell, int *curr_pipe);
void	make_our_env(t_shell *shell);
int		check_pipe_error(char *str, int i);
void	skip_to_option(char *cmd, t_echo *e_vars, char **parse_cmd);
int		found_redir(char *cmd);
int		var_2_value(t_shell *s, int *i, char *cmd, char *text);
//----------------------------------------------------------ERRORS
// exit and display error annd it call free struct
int		ft_exit(t_shell *shell, char *err);
//cmd not fount error
void	error_cmd_not_found(t_shell *s, char *cmd);
int		bash_syntax_error(t_shell *s, int err);
void	bash_error_w_filename(t_shell *s, char *file);
// error when there is only 1 quote
void	quotes_error(t_shell *s);

#endif
