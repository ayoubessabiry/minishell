/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_returns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 04:16:54 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/06/17 04:16:55 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	return_helper(char **arg, char **r, char **s, int j)
{
	if (**r && strcmp(*r, "|"))
	{
		free (*s);
		free (*r);
		printf(RED"minishel: Parse error\n"RESET);
		g_status = 258;
		return (0);
	}
	while ((*arg)[j] && (*arg)[j] != '|')
	{
		if ((*arg)[j] == '"' || (*arg)[j] == '\'')
		{
			j = check_quotes((*arg), j, s);
			if (j < 0)
			{
				free(*s);
				free(*r);
				printf(RED"minishell: unclosed quotes\n"RESET);
				return (0);
			}
		}
		else
			*s = ft_strjoin(*s, (*arg)[j++]);
	}
	return (j);
}

int	return_check(char *arg, int j)
{
	if (!j || (!arg[j] && arg[j - 1] == '|'))
	{
		printf(RED"minishel: error\n"RESET);
		return (0);
	}
	return (j);
}

int	first_pipe_check(char **arg)
{
	*arg = filter_space(*arg);
	if ((*arg)[0] == '|')
	{
		printf(RED"minishell: syntax error\n"RESET);
		return (0);
	}
	return (1);
}
