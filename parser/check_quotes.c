/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:31:17 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/04/25 18:15:55 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_dollar(char *s, int i)
{
	return ((i == 0 && s[i] == '$')
		|| (i > 0 && s[i] == '$' && s[i - 1] != '\\'));
}

char	*get_dollar_value(t_shell *s, char *str, int *j)
{
	int		start;
	char	*value;
	char	*var;
	int		spc;

	spc = 0;
	start = *j;
	if (str[*j] && ft_isprint(str[*j])
		&& !ft_isalnum(str[*j]) && str[*j] != '_')
	{
		while (str[*j] && str[*j] != ' ')
			(*j)++;
		return (ft_substr(str, start - 1, *j - start + 2));
	}
	while (str[*j] && (ft_isalnum(str[*j]) || str[*j] == '_'))
		(*j)++;
	value = ft_substr(str, start, *j - start);
	(*j)--;
	if (!value)
		exit(1);
	var = get_envar_value(s, value);
	ft_free(value);
	if (!var)
		return (ft_strdup(""));
	return (var);
}

static void	doubleqts_content(t_shell *s, char **arg, int i)
{
	int		j;
	int		k;
	char	*tmp;
	char	*var;

	k = 0;
	j = 0;
	tmp = malloc(sizeof(char) * (1000));
	if (!tmp)
		exit(1);
	ft_memset(tmp, 0, 1000);
	while (arg[i][++j] && arg[i][j + 1])
	{
		if (is_dollar(arg[i], j))
		{
			j++;
			var = get_dollar_value(s, arg[i], &j);
			k = ft_strlcat(tmp, var, 1000);
			ft_free(var);
		}
		else
			tmp[k++] = arg[i][j];
	}
	tmp[k] = 0;
	str_replace(&arg[i], tmp);
}

static void	singleqts_content(char **arg, int i)
{
	int		j;
	int		k;
	char	*tmp;

	j = 0;
	k = 0;
	tmp = malloc(sizeof(char) * (1000));
	if (!tmp)
		exit(1);
	while (arg[i][j])
	{
		if (arg[i][j] != '\'')
			tmp[k++] = arg[i][j];
		j++;
	}
	tmp[k] = 0;
	str_replace(&arg[i], tmp);
}

void	check_quotes(t_shell *s, char **arg, int i)
{
	if (arg[i][0] == '\'')
		s->single_qts = 1;
	else if (arg[i][0] == '\"')
		s->double_qts = 1;
	if (s->single_qts)
		singleqts_content(arg, i);
	else if (s->double_qts)
		doubleqts_content(s, arg, i);
	s->double_qts = 0;
	s->single_qts = 0;
}
