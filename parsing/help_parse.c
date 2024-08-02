/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:52:05 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/08/19 20:06:04 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	expand_fetcher(char *s, int j, t_two_strings *t_s)
{
	char	*exp;
	char	*tmp;
	int		g;

	exp_init(&exp, s, &g, j);
	while (s[j] && !is_space(s[j]) && s[j] != '"')
	{
		exp = ft_strjoin(exp, s[j++]);
		if (s[j] == '$' || exp_v(s[j], g))
			break ;
		if (s[j] == '\'')
		{
			t_s->q = 0;
			break ;
		}
	}
	tmp = exp;
	exp = expand(exp + 1, t_s->env);
	free(tmp);
	while (s[j] && is_space(s[j]))
		exp = ft_strjoin(exp, s[j++]);
	t_s->r = ft_strjoin_str(t_s->r, exp);
	free(exp);
	return (j);
}

int	rm_quotes(char *s, int i, t_two_strings *t_s)
{
	if (s[i] == '"')
	{
		i++;
		while (s[i] && (s[i] != '"'))
		{
			if (s[i] == '$')
				return (expand_fetcher(s, i, t_s));
			t_s->r = ft_strjoin(t_s->r, s[i++]);
		}
		i++;
	}
	else if (s[i] == '\'')
	{
		i++;
		while (s[i] && (s[i] != '\''))
			t_s->r = ft_strjoin(t_s->r, s[i++]);
	}
	return (++i);
}

int	prepare_cmd(char *s, int j, int k, t_two_strings *t_s)
{
	j = skip_space(j, s, &t_s->q);
	while (j < (int)ft_strlen(s) && s[j]
		&& k && !is_space(s[j]) && !is_valid_del(s[j]))
	{
		if (s[j] == '"' || s[j] == '\'')
			j = rm_quotes(s, j, t_s);
		else
		{
			if (s[j] == '$' && ft_strcmp(t_s->s, "<<"))
				return (expand_fetcher(s, j, t_s));
			t_s->r = ft_strjoin(t_s->r, s[j++]);
		}
	}
	while (j < (int)ft_strlen(s) && s[j] && !k)
	{
		if (s[j] == '\'')
			t_s->q = !t_s->q;
		if (s[j] == '$' && !t_s->q)
			return (expand_fetcher(s, j, t_s));
		if (parser_helper_helper(s, j) || !s[j])
			break ;
		t_s->r = ft_strjoin(t_s->r, s[j++]);
	}
	return (j);
}

int	del_count(char *str)
{
	int		i;
	int		j;
	int		count;
	char	*s;

	count = 0;
	i = 0;
	while (i < (int)ft_strlen(str))
	{
		j = i;
		s = ft_strdup("");
		while (is_valid_del(str[j]))
			s = ft_strjoin(s, str[j++]);
		if (*s && check_del(s))
			count++;
		free(s);
		i = j + 1;
	}
	return (count);
}

int	check_del(char *s)
{
	return (!ft_strcmp(s, "<<") || !ft_strcmp(s, ">>")
		|| !ft_strcmp(s, "<") || !ft_strcmp(s, ">"));
}
