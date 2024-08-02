/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 02:16:28 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/06/17 02:16:28 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*filter_space(char *str)
{
	char	*filtered;
	size_t	i;
	size_t	j;
	int		s;

	i = 0;
	j = 0;
	s = ft_strlen(str) - 1;
	if (!str[0])
	{
		free(str);
		return ("");
	}
	while (s > 0 && is_space(str[s]))
		s--;
	while (is_space(str[i]))
		i++;
	if ((!i && s == (int)ft_strlen(str) - 1) || s <= 0)
		return (str);
	filtered = malloc(s - i + 2);
	while (i <= (size_t)s && s <= (int)ft_strlen(str) - 1)
		filtered[j++] = str[i++];
	filtered[j] = '\0';
	free(str);
	return (filtered);
}

int	check_quotes(char *arg, int i, char **s)
{
	if (arg[i] == '"')
	{
		*s = ft_strjoin(*s, arg[i++]);
		while (arg[i] && (arg[i] != '"'))
			*s = ft_strjoin(*s, arg[i++]);
	}
	else if (arg[i] == '\'')
	{
		*s = ft_strjoin(*s, arg[i++]);
		while (arg[i] && (arg[i] != '\''))
			*s = ft_strjoin(*s, arg[i++]);
	}
	if (!arg[i])
		return (-1);
	else
		*s = ft_strjoin(*s, arg[i++]);
	return (i);
}
