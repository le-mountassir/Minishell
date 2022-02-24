/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 21:33:40 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/02/24 10:58:52 by ahel-mou         ###   ########.fr       */
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

typedef struct minishell
{
	char		*rl_return; //  user input
	char		**env; 		// envirement variavle
	char		**terminal;
	char		*cd_path;
	int			num_of_cmd;
}				t_vars;

//-----------------------------------------------------> Utils
void		exec_cmd(t_vars *unit, char **cmd);
char		*find_path(char *command);
int			cmp_with_homemade(char **cmd, t_vars *unit);

//-----------------------------------------------------> parasing utils
void		handle_rl_input(t_vars   *unit); //--> 
char		*rm_space(t_vars *unit);

//-----------------------------------------------------> commands
int		ft_exit(t_vars	*unit); // done || literally just exit dial c no need to use kill
int		ft_cd(t_vars *unit);
int		ft_unset(t_vars *unit);
int		ft_pwd(t_vars *unit);
int		ft_export(t_vars *unit);
int		ft_env(t_vars *unit); // done || prints all the envirement variables
int		ft_echo(char **cmd); //
void	env_var(char **cmd); // done || prints the value of an envirement variable


#endif
