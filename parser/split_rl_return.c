/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_rl_return.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:31:00 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/04/25 18:16:22 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	skip_quotes_unti_pipe(t_shell *sh, char *rl_return,
		int i, int quote)
{
	int	q;

	q = 1;
	i++;
	while (rl_return[i])
	{
		if (is_quote(rl_return, i, quote))
			q++;
		if ((rl_return[i + 1] == '|' && q % 2 == 0) || !rl_return[i + 1])
			break ;
		i++;
	}
	if (q % 2 == 1)
		quotes_error(sh);
	return (i);
}

static char	*cpy_until_pipe(t_shell *sh, char *rl_return, int *i)
{
	int		end;
	int		start;

	start = *i;
	while (rl_return[*i])
	{
		if (rl_return[*i] == '\'')
			*i = skip_quotes_unti_pipe(sh, rl_return, *i, '\'');
		else if (rl_return[*i] == '"')
			*i = skip_quotes_unti_pipe(sh, rl_return, *i, '"');
		if (rl_return[*i] == '|' || !rl_return[*i + 1])
		{
			if ((check_pipe_error(rl_return, *i) && rl_return[*i] == '|')
				|| rl_return[0] == '|')
				bash_syntax_error(sh, 2);
			end = *i;
			if (!rl_return[*i + 1])
				end++;
			return (ft_substr(rl_return, start, end - start));
		}
		(*i)++;
	}		
	return (NULL);
}

static char	**fill_arr(t_shell *sh, int num_of_cmds, char *rl_return)
{
	int		i;
	int		k;
	char	**arr;

	i = 0;
	k = 0;
	arr = (char **)malloc(sizeof(char *) * (num_of_cmds + 1));
	if (!arr)
		return (NULL);
	while (!sh->input_error && k < num_of_cmds)
	{
		while (rl_return[i] && rl_return[i] == '|')
			i++;
		arr[k] = cpy_until_pipe(sh, rl_return, &i);
		if (!arr[k])
		{
			free_arr(arr);
			return (NULL);
		}
		k++;
	}
	arr[k] = NULL;
	return (arr);
}

static int	commands_counter(t_shell *sh, char *rl_return)
{
	int	i;
	int	count;

	if (!rl_return)
		return (0);
	i = -1;
	count = 0;
	while (rl_return[++i])
	{
		if (rl_return[i] == '\'')
			i = skip_quotes_unti_pipe(sh, rl_return, i, '\'');
		else if (rl_return[i] == '"')
			i = skip_quotes_unti_pipe(sh, rl_return, i, '"');
		if ((rl_return[i] != '|' && rl_return[i + 1] == '|')
			|| (rl_return[i] != '|' && rl_return[i + 1] == '\0'))
			count++;
	}
	return (count);
}

int	split_commands(t_shell *shell, char *rl_return)
{
	int		num_of_cmds;

	num_of_cmds = commands_counter(shell, rl_return);
	shell->cmd = fill_arr(shell, num_of_cmds, rl_return);
	if (!shell->cmd)
		return (ft_exit(shell, "cmd error\n"));
	shell->num_of_cmds = td_arr_len(shell->cmd);
	if (shell->input_error)
		free_arr(shell->cmd);
	free(rl_return);
	return (0);
}
