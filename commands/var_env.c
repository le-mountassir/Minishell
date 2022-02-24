/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 10:18:24 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/02/23 17:41:23 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

// done 

void	env_var(char **command)
{
	char	*var_rt;
	/*
		we call getenv so we can get the wanted inv_variable it takes the name of the variable
		we used ft_substr to remove the '$' and in case there is more than 1 '$' we tell substr to skip just the first one
		bcs if there ar multiple '$' we dont want the function to work
		then we check if the return is True, if its NULL it means that there is no env_variable with that name
	*/
	var_rt = getenv(ft_substr(command[0], 1, ft_strlen(command[0]) - 1)); 
	if(var_rt)
		printf("%s\n", var_rt);
}