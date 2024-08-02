/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_helper_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:35:52 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/08/18 18:35:52 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

int	allocc_size(char *s)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			i++;
			while (s[i] && s[i] != '"' && s[i] != '\'')
				i++;
		}
		if (is_valid_del(s[i]))
		{
			count++;
			while (is_valid_del(s[i]))
				i++;
		}
		if (!s[i])
			break ;
		i++;
	}
	return (count);
}

int	*del_indexes(char *s)
{
	t_ind_norm	ind_n;
	int			*arr;

	ind_n.j = 0;
	arr = malloc(sizeof(int) * (allocc_size(s)) + 10);
	ind_n.i = 0;
	while (s[ind_n.i])
	{
		if (s[ind_n.i] == '\'' || s[ind_n.i] == '\"')
		{
			ind_n.i++;
			while (s[ind_n.i] && s[ind_n.i] != '"' && s[ind_n.i] != '\'')
				ind_n.i++;
		}
		if (is_valid_del(s[ind_n.i]))
		{
			arr[ind_n.j++] = ind_n.i;
			while (is_valid_del(s[ind_n.i]))
				ind_n.i++;
		}
		if (!s[ind_n.i])
			break ;
		ind_n.i++;
	}
	return (arr);
}

int	file_col_help(int j, t_token *token, t_two_strings *t_s)
{
	while (j < (int)ft_strlen(token->token)
		&& is_valid_del(token->token[j]))
		t_s->s = ft_strjoin(t_s->s, token->token[j++]);
	return (j);
}

int	red_col_help(int i, t_token *tmp, char **s)
{
	while (is_valid_del(tmp->token[i]))
		*s = ft_strjoin(*s, tmp->token[i++]);
	return (i);
}

void	exp_init(char **s, char *ss, int *g, int j)
{
	*g = 0;
	*s = ft_strdup("");
	if (ss[j] && ss[j + 1] == '?')
		*g = 1;
}
