/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_norm2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:12:54 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/08/19 20:44:26 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
	{
		while (s[i])
			i++;
		return ((char *)&s[i]);
	}
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

int	check_def(char ***env, char *s)
{
	int		i;
	char	*tmp;
	char	*r;
	char	*stmp;

	i = -1;
	stmp = skip_s(s);
	while ((*env)[++i])
	{
		r = skip_s((*env)[i]);
		if (!ft_strcmp(r, stmp))
		{
			free (r);
			free (stmp);
			if (!ft_strchr(s, '='))
				return (1);
			tmp = (*env)[i];
			(*env)[i] = ft_strdup(s);
			free(tmp);
			return (1);
		}
		free (r);
	}
	free (stmp);
	return (0);
}

char	**ft_realoc(char **env, char *s)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = malloc(sizeof(char *) * (count_word(env) + 2));
	if (!new_env)
		return (NULL);
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i++] = ft_strdup(s);
	new_env[i] = 0;
	return (new_env);
}

void	change_oldpwd(char ***env)
{
	int		i;
	char	*pwd;
	char	**tmp;
	char	*tmp1;

	i = 0;
	pwd = NULL;
	while ((*env)[i] && ft_strncmp((*env)[i], "PWD", skip((*env)[i], '=')))
		i++;
	if ((*env)[i])
		pwd = ft_strdup((*env)[i] + 4);
	i = 0;
	while ((*env)[i] && ft_strncmp((*env)[i], "OLDPWD", skip((*env)[i], '=')))
		i++;
	if ((*env)[i])
		set_pwd(env, pwd, i);
	else if (pwd)
	{
		tmp = *env;
		tmp1 = ft_strjoin_str(ft_strdup("OLDPWD="), pwd);
		*env = ft_realoc(*env, tmp1);
		free (pwd);
		free (tmp1);
		ft_free (&tmp);
	}	
}

void	change_env(char ***env, char *s, char *new)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*env)[i] && ft_strncmp((*env)[i], s, skip((*env)[i], '=')))
		i++;
	if ((*env)[i])
	{
		tmp = (*env)[i];
		(*env)[i] = ft_strdup(new);
		free(tmp);
	}
}
