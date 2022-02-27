/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 22:37:44 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/02/26 16:34:02 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

// loading...

void fill_export(t_vars *unit)
{
	int i = 0;
	while(unit->env[i])
		i++;
	unit->export = malloc(sizeof(char *) * i);
	i = 0;
	while (unit->env[i])
	{
		unit->export[i] = unit->env[i];
		i++;
	}
	unit->export[i] = NULL;
	return ;
}

// if the return of strcmp is pos it means that the s1 should be after s2
int	ft_export(t_vars *unit)
{
	int i= 0;
	int j = 100;
	char *tmp;
	fill_export(unit);
	while (j)
	{
		i = 0;
		while(unit->export[i])
		{
			if (ft_strcmp(unit->export[i], unit->export[i+1]) > 0)
			{
				tmp = unit->export[i];
				unit->export[i] = unit->export[i+1];
				unit->export[i+1] = tmp;
			}
			i++;
		}
		j--;
	}
	i = 0;
	while (unit->export[i])
		printf("%s\n", unit->export[i++]);
	return(1);
}