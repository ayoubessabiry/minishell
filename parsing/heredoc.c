/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:13:37 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/06/20 19:13:37 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*create_file_names(t_token *tokens)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tokens->tokens_parts->file[i])
	{
		if (!ft_strcmp(tokens->tokens_parts->del[i], "<<"))
		{
			tmp = tokens->tokens_parts->file[i];
			tokens->tokens_parts->file[i] = ft_strjoin_str(ft_strdup("/tmp/"),
					tokens->tokens_parts->file[i]);
			free(tmp);
		}
		i++;
	}
	return (tokens);
}

void	heredoc_check(t_token *tokens, char **envp)
{
	int		red_ind;
	int		pid;
	t_token	*tmp;

	if (!tokens)
		return ;
	pid = heredoc_signal_init(tokens, 0);
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		tmp = tokens;
		while (tmp)
		{
			red_ind = -1;
			while (tmp->tokens_parts->del[++red_ind])
			{
				if (!ft_strcmp(tmp->tokens_parts->del[red_ind], "<<"))
					heredoc(tmp->tokens_parts->file[red_ind], envp);
			}
			tokens = create_file_names(tmp);
			tmp = tmp->next_token;
		}
		exit(g_status);
	}
	heredoc_signal_parent(pid, tokens, tokens);
}

char	*expand_heredoc(char *s, char **env)
{
	char	*str;
	char	*exp;
	int		i;
	int		q;

	str = ft_strdup("");
	i = 0;
	q = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			q = !q;
		if (s[i] == '$' && q == 0)
		{
			exp = expand(s + i + 1, env);
			str = ft_strjoin_str(str, exp);
			free(exp);
			i = ft_strlen(str);
		}
		if (s[i] != '\'')
			str = ft_strjoin(str, s[i]);
		i++;
	}
	free(s);
	return (str);
}

void	heredoc(char *delimiter, char **env)
{
	int		fd;
	char	*str;
	char	*file;

	(void)env;
	file = ft_strjoin_str(ft_strdup("/tmp/"), delimiter);
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	free(file);
	while (1)
	{
		str = readline("herdoc>");
		if (str && ft_strcmp(str, delimiter))
		{
			str = expand_heredoc(str, env);
			write(fd, str, ft_strlen(str));
			write(fd, "\n", 1);
		}
		else
		{
			free(str);
			break ;
		}
		free(str);
	}
	close(fd);
}
