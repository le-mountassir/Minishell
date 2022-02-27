/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 21:33:40 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/02/27 16:35:50 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h> // sigaction | signal ...
#include <string.h>
#include <dirent.h> //open dir | clode dir
#include <readline/readline.h> // rl
#include <readline/history.h> // rl
#include <fcntl.h>

typedef struct minishell
{
	char		*rl_return; //  user input
	char		**env; 		// envirement variavle
	char		**export;
}				t_vars;

//----------------------------------------------------->Minishell Utils
void		exec_cmd(t_vars *unit, char **cmd);
char		*find_path(char *command);
int			cmp_with_homemade(char **cmd, t_vars *unit);
void		ft_free_td(char **td_arr);
int			pipex(int num_of_cmds, char **commands, char **env);
//-----------------------------------------------------> parasing utils
void		handle_rl_input(t_vars   *unit); //--> 
char		*rm_space(char *cmd);

//-----------------------------------------------------> commands
int		ft_unset(t_vars *unit);
int		ft_export(t_vars *unit);
int		ft_cd(char **path);			// done
int		ft_exit(t_vars	*unit); 	// done 
int		ft_pwd(t_vars *unit);		// done
int		ft_env(t_vars *unit); 		// done
void	env_var(char **cmd);		// done

//---------//->echo
int		ft_echo(char **cmd); // loading
void    quotes_f_checker(int *quotes, int *checker, char cara); //echo utils
void    quotes_t_checker(int *quotes, int *checker, char cara); // echo utils
void    white_spaces(char cara); //echo utils
//---------//

#endif
