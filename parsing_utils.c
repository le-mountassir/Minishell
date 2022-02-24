/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:45:33 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/02/23 14:38:30 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

/*
	this function removes the spaces before a command eg: user input => "         ls -la"
*/
char	*rm_space(t_vars *unit)
{
	int	i;
	i = 0;
	char *fresh_cmd;
	
	while (unit->rl_return[i] == ' ')
		i++;
	fresh_cmd = ft_substr(unit->rl_return, i, ft_strlen(unit->rl_return) - i); // return a string without spaces
	free(unit->rl_return);
	return (fresh_cmd);
}