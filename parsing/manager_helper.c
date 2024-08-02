/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 21:23:09 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/08/17 21:23:09 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	skip_q(int i, char *s, char **ss)
{
	if (s[i] == '"')
	{
		*ss = ft_strjoin(*ss, s[i++]);
		while (s[i] && (s[i] != '"'))
			*ss = ft_strjoin(*ss, s[i++]);
	}
	else if (s[i] == '\'')
	{
		*ss = ft_strjoin(*ss, s[i++]);
		while (s[i] && s[i] != '\'')
			*ss = ft_strjoin(*ss, s[i++]);
	}
	return (++i);
}

int	skip_q_q(int i, char *s)
{
	if (s[i] == '"')
	{
		i++;
		while (s[i] && (s[i] != '"'))
			i++;
	}
	else if (s[i] == '\'')
	{
		i++;
		while (s[i] && (s[i] != '\''))
			i++;
	}
	return (++i);
}

int	parser_helper_helper(char *s, int j)
{
	int	i;
	int	*ind;
	int	size;

	ind = del_indexes(s);
	size = allocc_size(s);
	i = 0;
	while (i < size)
	{
		if (j == ind[i])
		{
			free(ind);
			return (1);
		}
		i++;
	}
	free(ind);
	return (0);
}
