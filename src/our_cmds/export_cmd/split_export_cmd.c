/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_export_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:30:10 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/06 15:45:47 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"


static char	**freetab(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (0);
}

static char	*split_cmd_to_words(const char *cmd, int *i)
{
	char	quote;
	int		j;
	char	*line;

	j = 0;
	line = (char *)malloc(sizeof(char) * (MAX + 1));
	if (!line)
		return (NULL);
	while (cmd[(*i)] && white_spaces(cmd[(*i)])) // we skip all the spaces betwen words
		(*i)++;
	while (cmd[(*i)] && !white_spaces(cmd[(*i)]))
	{
		if (cmd[(*i)] == '"' || cmd[(*i)] == '\'')
		{
			quote = cmd[(*i)]; // we store that quote in a variable so we can use it later to check when its colsed
			(*i)++; //we skip the first quote
			while (cmd[(*i)] && cmd[(*i)] != quote) // here we copy everything between the quotes
				line[j++] = cmd[(*i)++];
			(*i)++;
		}
		else if (!white_spaces(cmd[(*i)]))
			line[j++] = cmd[(*i)++];
	}
	line[j] = '\0';
	return (line);
}

static char	**fill_arr(int words, const char *cmd, char **arr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	arr[0] = NULL;
	while (j < words)
	{
		arr[j] = split_cmd_to_words(cmd, &i); // we use 'i' to keep track fin akhir mera 7bsna fl cmd
		if (!arr[j])
			return (freetab(arr));
		j++;
	}
	arr[j] = 0;
	return (arr);
}

static int	word_count(const char *cmd)
{
	int	i;
	int	quote;
	int	count;

	if (!cmd || !cmd[0])
		return (0);
	i = -1;
	count = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '"' || cmd[i] == '\'') // we check if the current char is a quote if yes we skip to the next quote (closing quote)
		{
			quote = cmd[i];
			i += 1;
			while (cmd[i] && cmd[i] != quote)
				i++;
		}
		if (cmd[i] && ((!white_spaces(cmd[i]) && white_spaces(cmd[i + 1])) // counts words using spaces ila kan current 7rf != space but next space so its a word
				|| (!white_spaces(cmd[i]) && cmd[i + 1] == '\0')))
			count++;
	}
	return (count);
}

char	**split_export_cmd(char const *cmd)
{
	int		words;
	char	**arr;

	if (!cmd)
		return (NULL);
	words = word_count(cmd);
	arr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (NULL);
	arr = fill_arr(words, cmd, arr);
	return (arr);
}
