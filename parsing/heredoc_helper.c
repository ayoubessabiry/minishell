/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 23:41:25 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/08/15 23:41:25 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	heredoc_valid(t_token *tokens)
{
	int	i;

	while (tokens)
	{
		i = 0;
		while (tokens->tokens_parts->del[i])
		{
			if (!ft_strcmp(tokens->tokens_parts->del[i], "<<"))
				return (1);
			i++;
		}
		tokens = tokens->next_token;
	}
	return (0);
}

void	heredoc_signal_parent(int pid, t_token *tmp, t_token *tokens)
{
	int	i;

	i = 0;
	waitpid(pid, &g_status, 0);
	tmp = tokens;
	tokens = heredoc_files_setter(tmp, tokens);
	signal(SIGINT, signal_handle);
}

int	heredoc_signal_init(t_token *tokens, int pid)
{
	pid = 1;
	signal(SIGINT, SIG_IGN);
	if (heredoc_valid(tokens))
		pid = fork();
	return (pid);
}

t_token	*heredoc_files_setter(t_token *tmp, t_token *tokens)
{
	int	red_ind;

	tmp = tokens;
	while (tmp)
	{
		red_ind = 0;
		while (tmp->tokens_parts->del[red_ind])
			red_ind++;
		tokens = create_file_names(tmp);
		tmp = tmp->next_token;
	}
	return (tokens);
}
