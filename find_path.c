/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:54:40 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/02/24 10:55:03 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

/* 
	checks if the user input is a command that exist in one the paths int the PATH var
*/
char	*find_path(char *command)
{
	char **paths;
	char *cmd;
	char *path;
	
	paths = ft_split(getenv("PATH"), ':'); 
	// ^ : splits the PATH var into multiple paths so we can check if that command exist in one of them
	
    cmd = ft_strjoin("/", command); // joins the user input with a '/' so we can join it here with one of the paths and check if that cmd exist in the path[i]
    while (*paths) //																	  |
    {			//						strjoin  		paths[0] = /bin  cmd = /ls	      |
        path = ft_strjoin(*paths, cmd);// 	 <============================================| path = /bin/ls
        if (!path)
            return (NULL);
        if (!access(path, F_OK)) // checks if the command exist in the current path if yes it breaks the loop and returns the path
            break ;
        free(path);
        paths++;
    }
    free(cmd);
    return (path);
}
