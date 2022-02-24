/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 22:36:58 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/02/24 16:20:48 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

// i think its done

void    white_spaces(char cara)
{
    if (cara == 'n')
        printf("\n");
    else if (cara == 't')
        printf("\t");
    else if (cara == 'v')
        printf("\v");
    else if (cara == 'r')
        printf("\r");
    else if (cara == 'f')
        printf("\f");
    else if (cara == '\\')
        printf("\\");
}

int ft_echo(char **cmd)
{
    int i = 1;
    int j;
    int quotes = 0;
    while (cmd[i])
    {
        j = 0;
        while (cmd[i][j])
        {
            if (cmd[i][j] == '"' && quotes == 1)
                printf("%c", cmd[j][i]);
            else if (cmd[i][j] == '\'' && quotes == 2)
                printf("%c", cmd[j][i]);

            if(quotes && (cmd[i][j] == '"' || cmd[i][j] == '\''))
                quotes = 0;
            else if(cmd[i][j] == '\'')   
                quotes = 1;
            else if (cmd[i][j] == '"')
                quotes = 2;
            
                
            if(cmd[i][j] != '"' && cmd[i][j] != '\'' && cmd[i][j] != '\\')
                printf("%c", cmd[i][j]);

            if(quotes && cmd[i][j] == '\\')
                white_spaces(cmd[i][++j]);
            j++;
        }
        i++;
        if (cmd[i])
            printf(" ");
    }
    // new line for the prompt
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
    