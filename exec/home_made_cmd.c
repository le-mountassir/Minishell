/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_made_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:59:11 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/02/23 17:00:47 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

// checks if the user input is one of the commands that we builed 
// than it call the implementation of that command

int    cmp_with_homemade(char **cmd, t_vars *unit)
{
    int i = 0;
    while (cmd[i])
    {
        if (!ft_strcmp(cmd[i], "exit"))
            return (ft_exit(unit));
        else if (!ft_strcmp(cmd[i], "cd"))
            return (ft_cd(unit));
        else if (!ft_strcmp(cmd[i], "echo"))
            return (ft_echo(cmd));
        else if (!ft_strcmp(cmd[i], "env"))
            return (ft_env(unit));
        else if (!ft_strcmp(cmd[i], "export"))
            return (ft_export(unit));
        else if (!ft_strcmp(cmd[i], "pwd"))
            return (ft_pwd(unit));
        else if (!ft_strcmp(cmd[i], "unset"))
            return (ft_unset(unit));
        i++;
    }
    return (0);
}