/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 14:16:03 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/29 17:14:41 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// we used strlcat so we can get an index on where it stopped joining
// we skip the dollar signe line: 23
static int	var_2_value(t_shell *s, int *i, char *cmd, char *text)
{
	int		k;
	char	*var;

	k = 0;
	(*i)++;
	var = get_dollar_value(s, cmd, i);
	k = ft_strlcat(text, var, ft_strlen(text) + ft_strlen(var));
	ft_free(var);
	(*i)++;
	return (k);
}

static void	sngl_quot(int *i, char *cmd, char *text, int *k)
{
	(*i) += 1;
	while (cmd[(*i)] != '\'')
	{
		text[(*k)] = cmd[(*i)];
		(*k)++;
		(*i)++;
	}
	(*i) += 1;
}

static void	dbq_handler(t_shell *s, t_echo *e_vars)
{
	e_vars->i += 1;
	while (e_vars->cmd[e_vars->i] != '\"')
	{
		if (is_dollar(e_vars->cmd, e_vars->i)
			&& e_vars->cmd[e_vars->i + 1] == '?')
		{
			e_vars->i += 2;
			e_vars->tmp = ft_itoa(s->cmdretval);
			e_vars->k = ft_strlcat(e_vars->txt, e_vars->tmp, 10);
		}
		else if (is_dollar(e_vars->cmd, e_vars->i))
			e_vars->k = var_2_value(s, &(e_vars->i),
					e_vars->cmd, e_vars->txt);
		else
			e_vars->txt[e_vars->k++] = e_vars->cmd[e_vars->i++];
	}
	e_vars->i++;
}

static int	echoing(t_shell *s, t_echo *e_vars)
{
	if (e_vars->cmd[e_vars->i + 1] == '>'
		&& white_spaces(e_vars->cmd[e_vars->i]))
		return (0);
	while (white_spaces(e_vars->cmd[e_vars->i]))
	{
		if (!white_spaces(e_vars->cmd[e_vars->i + 1]))
			e_vars->txt[e_vars->k++] = e_vars->cmd[e_vars->i];
		e_vars->i++;
	}
	if (e_vars->cmd[e_vars->i] == '\'')
		sngl_quot(&(e_vars->i), e_vars->cmd, e_vars->txt, &(e_vars->k));
	else if (e_vars->cmd[e_vars->i] == '\"')
		dbq_handler(s, e_vars);
	else if (e_vars->cmd[e_vars->i] == '$' && e_vars->cmd[e_vars->i + 1] == '?')
	{
		e_vars->i += 2;
		e_vars->tmp = ft_itoa(s->cmdretval);
		e_vars->k = ft_strlcat(e_vars->txt, e_vars->tmp, 10);
	}
	else if (is_dollar(e_vars->cmd, e_vars->i))
		e_vars->k = var_2_value(s, &(e_vars->i), e_vars->cmd, e_vars->txt);
	else
		e_vars->txt[e_vars->k++] = e_vars->cmd[e_vars->i++];
	return (1);
}

void	echo_cmd(t_shell *s, char **parsed_cmd, char *cmd)
{
	t_echo	e_vars;

	e_vars.i = 1;
	e_vars.k = 0;
	e_vars.n_line = 0;
	e_vars.txt = malloc(ft_strlen(cmd) + 9999);
	e_vars.cmd = cmd;
	if (td_arr_len(parsed_cmd) == 1)
		write(1, "\n", 1);
	if (s->input_error)
		return ;
	skip_to_option(cmd, &e_vars, parsed_cmd);
	while (white_spaces(cmd[e_vars.i]))
		e_vars.i++;
	while (cmd[e_vars.i])
		if (!echoing(s, &e_vars))
			break ;
	ft_putstr_fd(e_vars.txt, 1);
	if (!e_vars.n_line)
		write(1, "\n", 1);
	free(e_vars.txt);
}
