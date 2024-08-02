/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parts_manager_return_error.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:06:31 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/07/01 17:06:31 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	skip_valid_del(int j, char *tp, char **s)
{
	while (is_valid_del(tp[j]))
		*s = ft_strjoin(*s, tp[j++]);
	j++;
	while (tp[j] && !is_valid_del(tp[j]) && !check_del(*s))
		j++;
	return (j);
}

int	return_error(char **s)
{
	free(*s);
	ft_putstr_fd(RED"Here : parse error\n"RESET, 2);
	g_status = 258;
	return (0);
}

int	red_check(char *tp)
{
	char	*s;
	int		j;

	j = 0;
	while (tp[j])
	{
		s = ft_strdup("");
		if (tp[j] == '"' || tp[j] == '\'')
			j = skip_q_q(j, tp);
		if (!tp[j])
		{
			free(s);
			break ;
		}
		if (is_valid_del(tp[j]))
		{
			j = skip_valid_del(j, tp, &s);
			j--;
			if (!tp[j] || is_valid_del(tp[j]) || !check_del(s) || tp[j] == '|')
				return (return_error(&s));
		}
		free(s);
		j++;
	}
	return (1);
}
