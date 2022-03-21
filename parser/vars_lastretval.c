/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_lastretval.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:31:25 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/19 11:20:03 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*var_2value(t_shell *shell, char *s)
{
	int		i;
	char	*var;
	char	*var_name;

	i = 1;
	while (s[i] && !white_spaces(s[i]))
		i++;
	var_name = ft_substr(s, 1, i - 1);
	if (!var_name)
		exit(1);
	var = get_envar_value(shell, var_name);
	if (!var)
	{
		var = ft_strdup("");
		if (!var)
			exit(1);
	}
	free(var_name);
	return (var);
}

static void	get_last_cmd_retval(t_shell s, char **arg, int i)
{
	int		j;
	int		k;
	int		l;
	char	*tmp;

	j = 2;
	tmp = malloc(sizeof(char) * 1000);
	if (!tmp)
		exit(1);
	l = ft_numlen(s.cmdretval);
	k = l;
	if (s.cmdretval == 0)
		tmp[0] = 0 + '0';
	while (s.cmdretval != 0 && l > 0)
	{
		tmp[--l] = s.cmdretval % 10 + '0';
		s.cmdretval /= 10;
	}
	while (arg[i][j])
		tmp[k++] = arg[i][j++]; // here we skip "$?" j =2; and copy everything after it to tmp
	tmp[k] = 0;
	str_replace(&arg[i], tmp);
}

void	check_var_or_retval(t_shell *s, char **arg, int i)
{
	char	*tmp;

	if (s->single_qts || s->double_qts)
		return ;
	if (!ft_strncmp("$?", arg[i], 2))
		get_last_cmd_retval(*s, arg, i);
	else if (starts_with("$", arg[i]) && !white_spaces(arg[i][1]) && ft_strcmp("$", arg[i]))
	{
		tmp = var_2value(s, arg[i]);
		if (!tmp)
			exit(1);
		str_replace(&arg[i], tmp);
	}
}
