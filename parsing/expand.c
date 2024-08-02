/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 21:38:37 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/06/17 21:38:37 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exp_v(char c, int g)
{
	return ((c >= 33 && c <= 35)
		|| (c >= 37 && c <= 47)
		|| (c >= 58 && c <= 62)
		|| (c == 64)
		|| (c >= 91 && c <= 94)
		|| (c >= 123 && c <= 125)
		|| (c >= 'a' && c <= 'z' && g)
		|| (c >= 'A' && c <= 'Z' && g)
		|| (c >= '0' && c <= '9' && g));
}

int	skip(char *str, char c)
{
	int	step;

	step = 0;
	while (str[step] && str[step] != c)
		step++;
	return (step);
}

char	*skipped(char *str, char n)
{
	int		i;
	char	*s;

	i = 0;
	s = ft_strdup("");
	while (str[i] && str[i] != n)
		s = ft_strjoin(s, str[i++]);
	return (s);
}

char	*expand(char *str, char **envp)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i++])
	{
		if (str[0] == '?')
			return (ft_itoa(g_status));
	}
	i = 0;
	tmp = skipped(envp[i], '=');
	while (envp[i] && ft_strcmp(str, tmp))
	{
		free(tmp);
		tmp = 0;
		i++;
		if (!envp[i])
			break ;
		tmp = skipped(envp[i], '=');
	}
	if (tmp)
		free(tmp);
	if (!envp[i])
		return (ft_strdup(""));
	return (ft_strdup(envp[i] + skip(envp[i], '=') + 1));
}
