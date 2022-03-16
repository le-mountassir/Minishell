/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:32:21 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/12 15:12:58 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	write2tmpfile(t_shell *s, char *word)
{
	write(s->file.tmpfd, word, ft_strlen(word));
	write(s->file.tmpfd, "\n", 1);
	ft_free(word);
}


static void	redir_heredoc(t_shell *s)
{
	close(s->file.tmpfd);
	if (s->file.here_doc)
		s->file.fdin = open("tmp_file", O_RDWR);
	if (s->file.fdin < 0)
		bash_error_w_filename(s, s->file.input_fd);
	unlink("tmp_file");
}

void	get_heredoc(t_shell *s, char *word)
{
	s->file.tmpfd = open("tmp_file", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (s->file.tmpfd < 0)
		ft_exit(s, "Tmpfile");
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		word = readline("Heredoc> ");
		if (!word)
		{
			ft_putstr_fd("here-doc error", 2);
			break ;
		}
		if (!ft_strcmp(word, s->file.stopword))
			break ;
		write2tmpfile(s, word);
	}
	ft_free(word);
	if (not_executable_cmd(s, s->cmd_with_args[0]))
	{
		ft_free(s->file.stopword);
		s->error_skip = 1;
		return ;
	}
	redir_heredoc(s);
	ft_free(s->file.stopword);
}
// checks if theres only the heredoc and no command after it bcs herdoc can execute cmds
int	only_hrdoc_with_nocmd(t_shell *s)
{
	char	*word;

	if (!s->file.stopword || (s->file.stopword && s->cmd_with_args[0]))
		return (0);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		word = readline("Heredoc> ");
		if (!word)
			break;
		if (!ft_strcmp(word, s->file.stopword))
			break ;
		free(word);
	}
	free(word);
	free(s->file.stopword);
	s->file.stopword = 0;
	checkfile_redir(s);
	return (1);
}