/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smounir <smounir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:06:56 by smounir           #+#    #+#             */
/*   Updated: 2022/05/21 14:06:56 by smounir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*split_pipes_helper(char **r, char **s, t_token **tokens)
{
	free(*r);
	free(*s);
	if (*tokens)
		free_tokens(tokens);
	return (0);
}

t_token	*split_with_pipes(char **arg)
{
	t_token			*tokens;
	t_two_strings	t_s;
	int				i;
	int				j;

	tokens = 0;
	i = 0;
	if ((*arg)[0] == '\0' || !first_pipe_check(arg))
		return (0);
	while ((*arg)[i])
	{
		j = i;
		init_strings(&t_s.s, &t_s.r);
		while ((*arg)[j] == '|')
			t_s.r = ft_strjoin(t_s.r, (*arg)[j++]);
		j = return_helper(arg, &t_s.r, &t_s.s, j);
		if (!j)
			return (0);
		if (!return_check(*arg, j))
			return (split_pipes_helper(&t_s.r, &t_s.s, &tokens));
		tokens = add_token(tokens, t_s.s);
		free_strings(&t_s.r, &t_s.s);
		i = j;
	}
	return (tokens);
}

int	all_quotes(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (!is_space(str[i]) && str[i] != '\'')
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

t_token	*parse_tokens(t_token *tokens, char **env)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		tmp->tokens_parts = init_parts(tmp);
		tmp->tokens_parts->del = collect_red(tmp);
		tmp->tokens_parts->file = collect_files(tmp, env);
		tmp->tokens_parts->cmd = collect_cmd(tmp, env);
		tmp->tokens_parts->cmd = filter_space(tmp->tokens_parts->cmd);
		tmp->tokens_parts->cmd_arg = filtered_args(tmp->tokens_parts->cmd);
		if (tmp && !tmp->tokens_parts->cmd[0])
			tmp->tokens_parts->cmd = 0;
		tmp = tmp->next_token;
	}
	return (tokens);
}
