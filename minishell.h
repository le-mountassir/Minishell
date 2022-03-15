/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:33:06 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/15 15:23:34 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "struct.h"
# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <termios.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define READ 0
# define WRITE 1
# define MAX 1000


/*
 * PARSING
 */
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



//Home made commands
void	exit_cmd(t_shell *shell);
void	cd_cmd(t_shell *shell);
void	tilde_handler(t_shell *shell); // handle the 'cd -'
void    display_export(t_shell *shell);
void	unset_cmd(t_shell *shell);
void	export_cmd(t_shell *shell);
char	**split_export_cmd(char const *str); // we use this function to split the command export into multipl words ||"cmd" "name" "args"|| ..

/*
 * EXECUTION
 */
void	start_shell(t_shell *s); //pre_executing part
void	execution(t_shell *s); // execution
int		only_hrdoc_with_nocmd(t_shell *s); // checks id there is only a heredoc without a cmd after it
int		not_executable_cmd(t_shell *s, char *cmd); // checks if the command is executable

int		not_pipeable_cmd(t_shell *s); // checks if the commands is pipe able means that it has an output
void	checkfile_redir(t_shell *s);
void	get_fds(t_shell *s, int i, int *pipe_fd);
void	get_heredoc(t_shell *s, char *word);
void	fork_failed(t_shell *s);
void	close_fds(t_shell *s);

/*
 * ENVIRONMENT
 */

int		change_var_value(t_shell *shell, char *var, char *value); // change *var value with *value
char	*get_envar_value(t_shell *shell, char *str); // returns the valus of the env variable
void	enver(t_shell *shell);
void	expoort(t_shell *shell, char *str);
char	*get_val(char *str);
int		alpharank(t_shell *shell, char *str);
void	sort_env(t_shell *shell);
int		is_sorted(char *s1, char *s2);
// void	dollar(t_shell *shell);
void	shell_levels(t_shell *shell);

/*
 * UTILS
 */
void	init_structure(t_shell *s, char **env);
void	reinit_structure(t_shell *s);
int		go_next_quote(t_shell *sh, char *cmd, int i, int quotes);
char	**split_cmd_ags(t_shell *sh, char *command, char c);
int	dbquote_check(char *cmd, int i, int quote);
int		is_quote(char *s, int i, int quotes);

void	free_arr(char **array);
void	free_redir(t_shell *s);
int		ft_exit(t_shell *shell, char *err);
int		starts_with(char *s1, char *s2);
int		valid_dbquote(char *s, int j, int Q);
int		not_doublequote(char *s, int j);
void	wait_pid(void);
void	reset_string(char **s, int i);
void	reset_shell(t_shell *s);
void	free_struct(t_shell *s);
void	ft_free(char *s);
void	str_replace(char **dst, char *src);
void	swap_file(t_shell *s, char **file, char **arg, int i);


//ERRORS
void	error_cmd_not_found(t_shell *s, char *cmd); //cmd not fount error
int		bash_error_unexpected_token(t_shell *s, int err);
void	bash_error_w_filename(t_shell *s, char *file);
void	quotes_error(t_shell *s);

#endif
