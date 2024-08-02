/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_norm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:47:28 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/08/16 11:47:01 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_expo(char ***env, int fd)
{
	int	i;
	int	j;
	int	f;

	i = 0;
	while ((*env)[i])
	{
		f = 0;
		ft_putstr_fd("declare -x ", fd);
		j = 0;
		while ((*env)[i][j])
		{
			write(fd, &(*env)[i][j], 1);
			if ((*env)[i][j] == '=')
			{
				write(fd, "\"", 1);
				f = 1;
			}
			j++;
		}
		if (f)
			write (fd, "\"", 1);
		ft_putstr_fd("\n", fd);
		i++;
	}
}

void	export(char ***env, char **s, int fd)
{
	int		i;
	int		f;

	f = 0;
	i = -1;
	if (*s)
	{
		while (s[++i])
		{
			if (!check_ide(s[i]))
			{
				ft_putstr_fd("not a valid identifier\n", 2);
				f = 1;
				g_status = 1;
			}
			else if (!check_def(env, s[i]))
				compose_three_lines(&s, i, env);
		}
	}
	else
		print_expo(env, fd);
	if (!f)
		g_status = 0;
}

int	count(char **s, char **env)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		j = 0;
		while (env[j])
		{
			if (!ft_strncmp(env[j], s[i], skip(env[j], '=')))
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int	check(char *env, char **s)
{
	int	j;

	j = 0;
	while (s[++j])
	{
		if (!ft_strncmp(env, s[j], skip(env, '=')))
			return (1);
	}
	return (0);
}

char	**unset(char **env, char **s)
{
	char	**new_env;
	int		i;
	int		k;

	k = 0;
	if (!count(s, env))
		return (env);
	new_env = malloc(sizeof(char *) * (count_word(env) - count(s, env) + 1));
	if (!new_env)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		if (!check(env[i], s))
			new_env[k++] = ft_strdup(env[i]);
	}
	new_env[k] = 0;
	ft_free(&env);
	g_status = 0;
	return (new_env);
}
