/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_norm5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:04:54 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/08/19 20:37:42 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_pwd(char ***env, char *pwd, int i)
{
	char	*tmp;
	char	*tmp2;

	if (!pwd)
	{
		tmp2 = (*env)[i];
		(*env)[i] = ft_strdup("OLDPWD=");
		free (tmp2);
		return ;
	}
	tmp = pwd;
	tmp2 = (*env)[i];
	(*env)[i] = ft_strjoin_str(ft_strdup("OLDPWD="), pwd);
	if (tmp)
		free (tmp);
	free (tmp2);
}

int	check_is_builtins(char	**cmd)
{
	return (!ft_strcmp("echo", cmd[0])
		|| !ft_strcmp("export", cmd[0])
		|| !ft_strcmp("unset", cmd[0])
		|| !ft_strcmp("env", cmd[0])
		|| !ft_strcmp("cd", cmd[0])
		|| !ft_strcmp("pwd", cmd[0])
		|| !ft_strcmp("exit", cmd[0]));
}

int	check_builtin(t_token *tokens, char ***env, int rw, int j)
{
	int	id;

	id = 0;
	if (j || tokens->next_token)
	{
		if (check_is_builtins(tokens->tokens_parts->cmd_arg))
		{
			id = fork();
			if (id == -1)
			{
				ft_putstr_fd(RED"Minishell : error while forking\n"RESET, 2);
				return (-1);
			}
			if (id == 0)
			{
				is_builtin(tokens->tokens_parts->cmd_arg, env, rw);
				exit(g_status);
			}
			wait(NULL);
			return (1);
		}
	}
	else
		return (is_builtin(tokens->tokens_parts->cmd_arg, env, rw));
	return (0);
}

char	*skip_s(char *s)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = malloc(skip(s, '=') + 1);
	while (s[i])
	{
		if (s[i] == '=')
			break ;
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
