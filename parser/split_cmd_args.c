/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:30:04 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/04/25 18:16:13 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cpy_between_quotes(char *cmd, char *arr, int i, char quote)
{
	int	j;

	j = 0;
	arr[j++] = cmd[i];
	while (cmd[++i] && !(cmd[i] == quote && cmd[i - 1] != '\\'))
	{
		if (quote == '\'' || dbquote_check(cmd, i, quote))
			arr[j++] = cmd[i];
	}
	arr[j] = cmd[i];
	arr[j + 1] = '\0';
	return (i + 1);
}

static int	cpystr(char *cmd, char *arr, int i)
{
	int	j;

	j = 0;
	while (cmd[i] && !white_spaces(cmd[i]))
		arr[j++] = cmd[i++];
	arr[j] = '\0';
	return (i);
}

static char	**fill_arr(int numof_words, char *cmd, char **arr)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (k < numof_words)
	{
		arr[k] = (char *)malloc(sizeof(char) * 1000);
		if (!arr[k])
		{
			free_arr(arr);
			return (NULL);
		}
		while (cmd[i] && white_spaces(cmd[i]))
			i++;
		if (cmd[i] == '\'')
			i = cpy_between_quotes(cmd, arr[k], i, '\'');
		else if (cmd[i] == '"')
			i = cpy_between_quotes(cmd, arr[k], i, '"');
		else
			i = cpystr(cmd, arr[k], i);
		k++;
	}
	arr[k] = 0;
	return (arr);
}

static int	word_count(t_shell *sh, char *cmd)
{
	int	i;
	int	count;

	if (!cmd)
		return (0);
	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'')
		{
			i = go_next_quote(sh, cmd, i, '\'');
			count++;
		}
		else if (cmd[i] == '"')
		{
			i = go_next_quote(sh, cmd, i, '"');
			count++;
		}
		else if ((!white_spaces(cmd[i]) && white_spaces(cmd[i + 1]))
			|| (!white_spaces(cmd[i]) && cmd[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

char	**split_cmd_args(t_shell *sh, char *command, char c)
{
	char	**words;
	int		numof_words;

	if (!command)
		return (NULL);
	(void)c;
	numof_words = word_count(sh, command);
	words = malloc(sizeof(char *) * (numof_words + 1));
	if (!words)
		return (NULL);
	return (fill_arr(numof_words, command, words));
}
