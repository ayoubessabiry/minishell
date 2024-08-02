/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parts_manager.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 01:50:03 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/06/18 01:50:03 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token_parts	*init_parts(t_token *token)
{
	token->tokens_parts = malloc(sizeof(t_token_parts));
	token->tokens_parts->del = ft_calloc(del_count(token->token) + 1,
			sizeof(char*));
	token->tokens_parts->file = malloc((del_count(token->token) + 1)
			* sizeof(char*));
	token->tokens_parts->cmd = ft_strdup("");
	return (token->tokens_parts);
}

char	**collect_red(t_token *tmp)
{
	char	*s;
	int		i;
	int		red_ind;

	i = 0;
	red_ind = 0;
	while (tmp->token[i])
	{
		s = ft_strdup("");
		if (tmp->token[i] == '"' || tmp->token[i] == '\'')
			i = skip_q_q(i, tmp->token);
		if (!tmp->token[i])
		{
			free(s);
			break ;
		}
		i = red_col_help(i, tmp, &s);
		if (*s)
			tmp->tokens_parts->del[red_ind++] = ft_strdup(s);
		free(s);
		if (tmp->token[i] != '"' && tmp->token[i] != '\'')
			i++;
	}
	tmp->tokens_parts->del[red_ind] = 0;
	return (tmp->tokens_parts->del);
}

void	init_zero(t_ind_norm *ind_n)
{
	ind_n->i = 0;
	ind_n->j = 0;
	ind_n->k = 0;
	ind_n->file_ind = 0;
}

char	**collect_files(t_token *token, char **env)
{
	t_ind_norm		ind_n;
	t_two_strings	t_s;

	t_s.env = env;
	init_zero(&ind_n);
	while (ind_n.i < (int)ft_strlen(token->token) && token->token[ind_n.i])
	{
		ind_n.j = ind_n.i;
		if (token->token[ind_n.j] == '"' || token->token[ind_n.j] == '\'')
			ind_n.j = skip_q_q(ind_n.j, token->token);
		init_strings(&t_s.s, &t_s.r);
		ind_n.j = file_col_help(ind_n.j, token, &t_s);
		if (*t_s.s && check_del(t_s.s))
				ind_n.k++;
		ind_n.j = prepare_cmd(token->token, ind_n.j, ind_n.k, &t_s);
		if (*t_s.r && ind_n.k)
		{
			token->tokens_parts->file[ind_n.file_ind++] = ft_strdup(t_s.r);
			ind_n.k = 0;
		}
		ind_n.i = ind_n.j;
		free_strings(&t_s.s, &t_s.r);
	}
	token->tokens_parts->file[ind_n.file_ind] = 0;
	return (token->tokens_parts->file);
}

char	*collect_cmd(t_token *token, char **env)
{
	t_ind_norm		ind_n;
	t_two_strings	t_s;

	t_s.env = env;
	init_zero(&ind_n);
	while (ind_n.i < (int)ft_strlen(token->token) && token->token[ind_n.i])
	{
		init_strings(&t_s.s, &t_s.r);
		ind_n.j = ind_n.i;
		if (parser_helper_helper(token->token, ind_n.j))
		{
			while (is_valid_del(token->token[ind_n.j]))
				t_s.s = ft_strjoin(t_s.s, token->token[ind_n.j++]);
		}
		if (*t_s.s && check_del(t_s.s))
				ind_n.k++;
		ind_n.j = prepare_cmd(token->token, ind_n.j, ind_n.k, &t_s);
		if (*t_s.r && !ind_n.k)
			token->tokens_parts->cmd = ft_strjoin_str(token->tokens_parts->cmd,
					t_s.r);
		ind_n.k = 0;
		ind_n.i = ind_n.j;
		free_strings(&t_s.s, &t_s.r);
	}
	return (token->tokens_parts->cmd);
}
