/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 22:36:58 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/02/26 15:48:39 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

// loading ...

int check_n(char *option)
{
    if (!ft_strcmp(option, "-n"))
        return (1);
    return (0);
}

int ft_echo(char **cmd)
{
    int i = 1;
    int j;
    int quotes = 0;
    int checker = 0;
    if (check_n(cmd[1]))
        i = 2;
    while (cmd[i])
    {
        j = 0;
        if (checker)
            checker = 0;
        while (cmd[i][j])
        {
                quotes_f_checker(&quotes, &checker, cmd[i][j]);

                if (quotes && (cmd[i][j] == '"' || cmd[i][j] == '\''))
                    printf("%c", cmd[i][j]);
                else if(cmd[i][j] != '"' && cmd[i][j] != '\'' && cmd[i][j] != '\\')
                    printf("%c", cmd[i][j]);

                quotes_t_checker(&quotes, &checker, cmd[i][j]);
                if(quotes && cmd[i][j] == '\\')
                    white_spaces(cmd[i][++j]);
            j++;
        }
        i++;
        if (cmd[i])
            printf(" ");
    }
    // new line for the prompt
    if (!check_n(cmd[1]))
        printf("\n");
    return (1);
}
            // here we check if there is a quote or d_quotes if yes we change the value of the var
            // we will need it to check if we need to print whitespaces or not 
    //++++++
            // here we check if the char is a " or ' if not we just print it bcs ' and " ar not printable characters in the command echo
    //++++++
            // if the quotes_var is true we check if the current char is '/' if yes we check the next character for whitespaces 
            // then we call the function white_spaces to change the vulue of the character into a whitespace '\n' '\t' '\r' '\v' ...
    //++++++
            // here we increment the value so we can skip the next char after '\' we dont want to print if bcs it was a whitespace
    //++++++
            // here we check the var_quotes is true and the current char is a ' or " if this statement is true it means 
            // that we finished reading whats inside "" or ''
            // we need this so the next time we find a '\n' '\t' '\v' ... we print it as a  normal char and not turn it to a whitespace
    //+++++++
            // here we check if the next string in the 2d_arry is true if yes we print space bcs bfr calling echo we splited the input using spaces
            // which means that there was a space in the inputs
    