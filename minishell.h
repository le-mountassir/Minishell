/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:33:06 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/21 13:30:54 by ahel-mou         ###   ########.fr       */
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

# define READ 0
# define WRITE 1

int	cld_proc;

typedef struct redirection
{
	int		here_doc; // checks if there is a heredoc
	int		input; // checks if there is an input file
	char	*stopword; // heredoc stop word
	char	*input_fd; // '<' input file
	char	*outfile; // '>>' '>' output file
	int		tmpfd; // fd of the tmpfile for the heredoc
	int		fdout; // file discriptor of the output file
	int		fdin; // fd of the input file
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

//---------------------------------------------------------parsing
int		split_commands(t_shell *shell, char *line); 
// split usser input with pipes into multiple commands
void	check_var_or_retval(t_shell *s, char **arg, int i); 
// checks if there is a $var and replace it with its vaue or if there is a $? last_retval
char	**split_cmd_args(t_shell *sh, char *command, char c);
// split a cmd with its args in a 2d_arr
char	**parse_cmd(t_shell *s, int i);
// split 1 cmd into a 2d_arr with its arguments using space ex: ls -al    2d_arr = [0] = ls | [1] = -al
void	check_dollar(t_shell *s, char **arg, int i);
void	check_quotes(t_shell *s, char **arg, int i);



//----------------------------------------------------------Home made commands
void	exit_cmd(t_shell *shell);
void	cd_cmd(t_shell *shell);
void	tilde_handler(t_shell *shell); // handle the 'cd -'
void    display_export(t_shell *shell);
void	unset_cmd(t_shell *shell);
void	export_cmd(t_shell *shell);
char	**split_export_cmd(char const *str); // we use this function to split the command export into multipl words ||"cmd" "name" "args"|| ..
void    echo_cmd(char **cmd);

//-----------------------------------------------------------exec
void	start_shell(t_shell *s); //pre_executing part
void	execution(t_shell *s); // execution
int		only_hrdoc_with_nocmd(t_shell *s); // checks id there is only a heredoc without a cmd after it
int		not_executable_cmd(t_shell *s, char *cmd); // checks if the command is executable

void	checkfile_redir(t_shell *s);
void	get_fds(t_shell *s, int i, int *pipe_fd);
void	get_heredoc(t_shell *s); // heredoc 
void	fork_failed(t_shell *s);
void	close_fds(t_shell *s);

//--------------------------------------------------------- ENVIRONMENT utils
int		change_var_value(t_shell *shell, char *var, char *value); // change *var value with *value
char	*get_envar_value(t_shell *shell, char *str); // returns the valus of the env variable
void	enver(t_shell *shell);
void	expoort(t_shell *shell, char *str);
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
void	remove_redir(char **s, int i); // replace the the redir and the file_name with whats left in the cmd | "< Makefile wc -l" ==> "wc -l"
void	str_replace(char **dst, char *src); // replace str in dst with src we use it to replace variable with the value and remove quotes while parsing
void	swap_file(t_shell *s, char **file, char **arg, int i);
void	free_arr(char **array);
void	free_redir(t_shell *s);
int		starts_with(char *s1, char *s2);
int		valid_dbquote(char *s, int j, int Q);
int		not_doublequote(char *s, int j);
void	wait_pid(void);
void	reset_shell(t_shell *s);
void	free_struct(t_shell *s);
void	ft_free(char *s);


//----------------------------------------------------------ERRORS
int		ft_exit(t_shell *shell, char *err); // exit and display error annd it call free struct
void	error_cmd_not_found(t_shell *s, char *cmd); //cmd not fount error
int		bash_syntax_error(t_shell *s, int err);
void	bash_error_w_filename(t_shell *s, char *file);
void	quotes_error(t_shell *s); // quotes mamsdodinch

#endif
