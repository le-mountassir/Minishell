/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 22:36:54 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/02/25 17:39:45 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

// done
/*
	the function |char *getcwd()| take's 2 args the 1st is a buffer 
	where getcwd() gonna store the current working dir 
	the second one is the size of that buffer
	curr_path contains the path
*/

int	ft_pwd(t_vars *unit)
{
	char	*curr_path;
	size_t	size;

	size = 500;
	curr_path = malloc(size);
	printf("%s\n", getcwd(curr_path, size));
	free(curr_path);
	return (1);
}
