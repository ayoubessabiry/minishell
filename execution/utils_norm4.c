/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_norm4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 10:34:30 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/08/16 19:49:37 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_digit(int c)
{
	if (c < '0' || c > '9')
		return (0);
	return (1);
}

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	check_ide(char *s)
{
	int	i;

	i = 0;
	if (!ft_isalpha(s[i]) && s[i] != '_')
		return (0);
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalpha(s[i]) && !ft_digit(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	compose_three_lines(char ***s, int i, char ***env)
{
	char	**tmp;

	tmp = *env;
	*env = ft_realoc(*env, (*s)[i]);
	ft_free (&tmp);
}

void	exe_helper_helper(t_var **var, int j)
{
	close((*var)->pfd[j][0]);
	close((*var)->pfd[j][1]);
}
