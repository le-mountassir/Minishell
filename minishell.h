/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:33:06 by ahel-mou          #+#    #+#             */
/*   Updated: 2023/02/07 15:44:08 by bel-amri         ###   ########.fr       */
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

void	start_shell(t_shell *s);
void	get_heredoc(t_shell *s);
void	execution(t_shell *shell);
void	dash_handler(t_shell *shell);

int		split_commands(t_shell *shell, char *line);
void	check_var_or_retval(t_shell *s, char **arg, int i);
char	**split_cmd_args(t_shell *sh, char *command, char c);
char	**parse_cmd(t_shell *s, int i);
void	check_dollar(t_shell *s, char **arg, int i);
void	check_quotes(t_shell *s, char **arg, int i);

void	exit_cmd(t_shell *shell, char **cmd);
void	cd_cmd(t_shell *shell, char **cmd);
void	display_export(t_shell *shell);
void	unset_cmd(t_shell *shell, char **cmd);
void	export_cmd(t_shell *shell);
char	**split_export_cmd(char const *str);
int		is_dollar(char *s, int i);
char	*get_dollar_value(t_shell *s, char *str, int *j);
void	echo_cmd(t_shell *s, char **parsed_cmd, char *original_cmd);

void	exec_cmd(t_shell *shell, int j);
int		only_hrdoc_with_nocmd(t_shell *s);
int		not_executable_cmd(t_shell *s, char *cmd);
int		home_made(t_shell *shell, int cmd_id);

void	checkfile_redir(t_shell *s);
void	get_fds(t_shell *s, int i, int *pipe_fd);
void	fork_failed(t_shell *s);
void	close_fds(t_shell *s);

int		change_var_value(t_shell *shell, char *var, char *value);
char	*get_envar_value(t_shell *shell, char *str);
void	enver(t_shell *shell);
void	assign_new_var(t_shell *shell, char *str);
char	*get_val(char *str);
void	sort_env(t_shell *shell);
int		is_sorted(char *s1, char *s2);
void	shell_levels(t_shell *shell);

void	init_structure(t_shell *s, char **env);
void	reinit_structure(t_shell *s);
int		go_next_quote(t_shell *sh, char *cmd, int i, int quotes);
char	**split_cmd_ags(t_shell *sh, char *command, char c);
int		dbquote_check(char *cmd, int i, int quote);
int		is_quote(char *s, int i, int quotes);
void	remove_redir(char **s, int i);
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
int		ft_exit(t_shell *shell, char *err);
void	error_cmd_not_found(t_shell *s, char *cmd);
int		bash_syntax_error(t_shell *s, int err);
void	bash_error_w_filename(t_shell *s, char *file);
void	quotes_error(t_shell *s);

#endif
