/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 14:16:03 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/26 18:31:28 by ahel-mou         ###   ########.fr       */
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
	k = ft_strlcat(text, var, 1000);
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

static void	handle_ret_val(t_shell *s, int *i, int *k, char *text)
{
	char	*num;

	(*i) += 2;
	num = ft_itoa(s->cmdretval);
	(*k) = ft_strlcat(text, num, 10);
}

static void	echoing(t_shell *s, t_echo *e_vars)
{
	if (e_vars->cmd[e_vars->i] == '\'')
		sngl_quot(&(e_vars->i), e_vars->cmd, e_vars->txt, &(e_vars->k));
	else if (e_vars->cmd[e_vars->i] == '\"')
	{
		e_vars->i += 1;
		while (e_vars->cmd[e_vars->i] != '\"')
		{
			if (is_dollar(e_vars->cmd, e_vars->i)
				&& e_vars->cmd[e_vars->i + 1] == '?')
				handle_ret_val(s, &(e_vars->i), &(e_vars->k), e_vars->txt);
			else if (is_dollar(e_vars->cmd, e_vars->i))
				e_vars->k = var_2_value(s, &(e_vars->i),
						e_vars->cmd, e_vars->txt);
			else
				e_vars->txt[e_vars->k++] = e_vars->cmd[e_vars->i++];
		}
		e_vars->i++;
	}
	else if (e_vars->cmd[e_vars->i] == '$' && e_vars->cmd[e_vars->i + 1] == '?')
		handle_ret_val(s, &(e_vars->i), &(e_vars->k), e_vars->txt);
	else if (is_dollar(e_vars->cmd, e_vars->i))
		e_vars->k = var_2_value(s, &(e_vars->i), e_vars->cmd, e_vars->txt);
	else
		e_vars->txt[e_vars->k++] = e_vars->cmd[e_vars->i++];
}

void	echo_cmd(t_shell *s, char **parsed_cmd, char *cmd)
{
	t_echo	e_vars;

	e_vars.i = 1;
	e_vars.k = 0;
	e_vars.n_line = 0;
	e_vars.txt = malloc(10000);
	e_vars.cmd = cmd;
	if (td_arr_len(parsed_cmd) == 1)
		write(1, "\n", 1);
	if (s->input_error)
		return ;
	if (!ft_strcmp(parsed_cmd[1], "-n"))
		e_vars.n_line = 1;
	e_vars.i = 5;
	if (e_vars.n_line)
		e_vars.i = 8;
	while (white_spaces(cmd[e_vars.i]))
		e_vars.i++;
	while (cmd[e_vars.i])
		echoing(s, &e_vars);
	ft_putstr_fd(e_vars.txt, 1);
	if (!e_vars.n_line)
		write(1, "\n", 1);
	free(e_vars.txt);
}
