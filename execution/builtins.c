/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammez <brogrammez@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 22:27:13 by brogrammez        #+#    #+#             */
/*   Updated: 2022/05/24 22:27:13 by brogrammez        ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_word(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	**get_env(char **s)
{
	char	**env;
	int		i;

	i = 0;
	env = malloc(sizeof(char *) * (count_word(s) + 1));
	if (!env)
		return (NULL);
	while (s[i])
	{
		env[i] = ft_strdup(s[i]);
		i++;
	}
	env[i] = 0;
	return (env);
}	

void	echo(char **s, int fd)
{
	int	i;
	int	f;

	f = 0;
	i = 0;
	while (s[i])
	{
		if (!check_op(s[i]))
			break ;
		f = 1;
		i++;
	}
	while (s[i])
	{
		ft_putstr_fd(s[i], fd);
		if (s[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (!f)
		ft_putstr_fd("\n", fd);
	g_status = 0;
}

void	cd(char *path, char ***env)
{
	char	*p;
	char	*tmp;

	if (chdir(path) == -1)
	{
		ft_putstr_fd("no such file or directory\n", 2);
		g_status = 1;
		return ;
	}
	change_oldpwd(env);
	p = getcwd(NULL, 0);
	if (!p)
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd:"
			"cannot access parent directories: No such file or directory\n", 2);
		g_status = 1;
		return ;
	}
	tmp = p;
	p = ft_strjoin_str(ft_strdup("PWD="), p);
	free(tmp);
	change_env(env, "PWD", p);
	free (p);
	g_status = 0;
}

void	pwd(char **env, int fd)
{
	int		i;
	char	*s;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PWD", skip(env[i], '=')))
		i++;
	if (env[i])
	{
		ft_putstr_fd(env[i] + (skip(env[i], '=') + 1), fd);
		ft_putstr_fd("\n", fd);
	}
	else
	{
		s = getcwd(NULL, 0);
		ft_putstr_fd(s, fd);
		ft_putstr_fd("\n", fd);
		free(s);
	}
	g_status = 0;
}
