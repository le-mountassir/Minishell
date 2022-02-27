/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:09:56 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/02/25 17:37:42 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

void	quotes_f_checker(int *quotes, int *checker, char cara)
{
	if (*quotes == 1 && (cara == '\''))
	{
		*quotes = 0;
		(*checker)++;
	}
	else if (*quotes == 2 && (cara == '"'))
	{
		*quotes = 0;
		(*checker)++;
	}
}

void	quotes_t_checker(int *quotes, int *checker, char cara)
{
	if (!(*quotes) && cara == '\'' && !(*checker))
		*quotes = 1;
	else if (!(*quotes) && cara == '"' && !(*checker))
		*quotes = 2;
}

void	white_spaces(char cara)
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
