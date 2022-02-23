/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 21:33:26 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/02/23 14:43:56 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./libft/libft.h"

void	sigs_listener(int sig)
{
	int pid = getpid();
	if (sig == 2)
	{
		// readline("Minishell~$:");
		return ;
	}
}

int main(int c, char **v, char **envir)
{
	t_vars	unit;

	// printf("pid : %d\n", getpid());
	while(1)
	{
		// signal(SIGINT, sigs_listener);
		unit.env = envir;
		unit.rl_return = readline("Minishell~$:"); // prints a promp and returns the user input as char*
		if (!unit.rl_return)
			return 0;
		add_history(unit.rl_return); 
		// add_history saves the user input so we can have a working hitory, use down and up arrow to navigate
		handle_rl_input(&unit); // parsing
		// while(1);
	}
}