/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:31:29 by ahel-mou          #+#    #+#             */
/*   Updated: 2022/03/28 11:01:28 by ahel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**get_paths(t_shell *shell)
{
	char	**ret;
	char	*env;

	env = get_envar_value(shell, "PATH");
	if (!env)
		return (NULL);
	else if (ft_strlen(env) == 0)
		return (NULL);
	ret = ft_splitpath(env, ':');
	if (!ret)
	{
		free(env);
		exit(1);
	}
	free (env);
	return (ret);
}

static void	init_fileredir(t_shell *struc)
{
	struc->file.tmpfd = 0;
	struc->file.fdin = 0;
	struc->file.fdout = 0;
	struc->file.over_write = 0;
	struc->file.append_f = 0;
	struc->file.input = 0;
	struc->file.here_doc = 0;
	struc->file.stopword = 0;
	struc->file.input_fd = 0;
	struc->file.outfile = 0;
}

// create a copy of the env and store it in the struct
static void	init_our_env(t_shell *shell, char **env)
{
	int		i;

	if (!env[0])
	{
		make_our_env(shell);
		return ;
	}	
	i = td_arr_len(env);
	shell->our_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!shell->our_env)
		exit(1);
	i = 0;
	while (env[i])
	{
		shell->our_env[i] = ft_strdup(env[i]);
		if (!shell->our_env[i])
			exit(1);
		i++;
	}
	shell->our_env[i] = 0;
	if (shell->our_env[0])
		sort_env(shell);
}

// Init all the vars in the struct to null or 0
void	init_structure(t_shell *struc, char **env)
{
	struc->our_env = 0;
	init_our_env(struc, env);
	struc->single_qts = 0;
	struc->double_qts = 0;
	struc->num_of_cmds = 0;
	struc->home_made_cmd = 0;
	struc->cmdnotfound = 0;
	struc->cmdretval = 0;
	struc->input_error = 0;
	struc->file.fdin = READ;
	struc->file.fdout = WRITE;
	struc->cmd = 0;
	struc->cmd_with_args = 0;
	struc->var = 0;
	init_fileredir(struc);
	struc->path = get_paths(struc);
}

void	reinit_structure(t_shell *struc)
{
	struc->input_error = 0;
	init_fileredir(struc);
	struc->file.fdin = READ;
	struc->file.fdout = WRITE;
	struc->single_qts = 0;
	struc->double_qts = 0;
	struc->num_of_cmds = 0;
	struc->home_made_cmd = 0;
	struc->cmd = 0;
	struc->cmd_with_args = 0;
	struc->var = 0;
	free_arr(struc->path);
	struc->path = get_paths(struc);
	if (!struc->path)
	{
		struc->path = malloc(sizeof(char *));
		struc->path[0] = NULL;
	}
}
