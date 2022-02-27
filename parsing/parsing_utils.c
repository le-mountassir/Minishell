/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:45:33 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/02/27 13:58:40 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

/*
	this function removes the spaces before a command eg: user input => "         ls -la"
*/
char	*rm_space(char *cmd)
{
	int	i;
	i = 0;
	char *fresh_cmd;
	
	while (cmd[i] == ' ')
		i++;
	fresh_cmd = ft_substr(cmd, i, ft_strlen(cmd) - i); // return a string without spaces
	// free(cmd);
	return (fresh_cmd);
}