/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:48:56 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/08/19 19:53:48 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp("PATH", env[i], 4))
		i++;
	if (!env[i])
	{
		ft_putstr_fd(RED"Minishell : no such file or directory\n"RESET, 2);
		g_status = 127;
		return (NULL);
	}
	return (ft_split(env[i] + 5, ':'));
}

char	**get_cmd(char **cmd, char **path)
{
	int		i;

	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], '/');
		path[i] = ft_strjoin_str(path[i], cmd[0]);
		if (access(path[i], F_OK) == 0)
		{
			free(cmd[0]);
			cmd[0] = path[i];
			while (path[++i])
				free(path[i]);
			free(path);
			return (cmd);
		}
		free(path[i]);
		i++;
	}
	ft_putstr_fd(RED"command not found\033[0m\n", 2);
	free(path);
	g_status = 127;
	return (NULL);
}

int	exe_helper(t_token *tokens, t_var *var, char ***env, int j)
{
	signal_ign();
	var->id[j] = fork();
	if (var->id[j] == -1)
	{
		ft_putstr_fd(RED"Minishell : error while forking\n"RESET, 2);
		return (-1);
	}
	if (var->id[j] == 0)
	{
		signal_reset();
		if (j && var->rd == 0)
			var->rd = var->pfd[j - 1][0];
		dup2(var->rd, 0);
		dup2(var->rw, 1);
		if (tokens->next_token)
			exe_helper_helper(&var, j);
		if (execve(var->cmd[0], var->cmd, *env) == -1)
		{
			ft_putstr_fd(RED"Minishell : command not found\n"RESET, 2);
			g_status = 127;
			exit (g_status);
		}
	}
	return (1);
}

void	ft_close(t_token *tokens, int **pfd, int j)
{
	if (tokens->next_token)
		close(pfd[j][1]);
	if (j)
	{
		close(pfd[j - 1][0]);
		free(pfd[j - 1]);
	}
}

int	exe_cmd(t_token *tokens, char ***env, t_var *var, int j)
{
	if (tokens->next_token)
	{
		var->pfd[j] = malloc (sizeof(int) * 2);
		if (pipe(var->pfd[j]) == -1)
		{
			ft_putstr_fd(RED"Minishell : error while open a pipe\n"RESET, 2);
			return (-1);
		}
		if (var->rw == 1)
			var->rw = var->pfd[j][1];
	}
	if (tokens->tokens_parts->cmd)
	{
		if (!check_builtin(tokens, env, var->rw, j))
		{
			var->cmd = get_cmd_to_exe(tokens->tokens_parts->cmd_arg, env);
			if (var->cmd)
				exe_helper(tokens, var, env, j);
		}
	}
	else
		g_status = 1;
	ft_close(tokens, var->pfd, j);
	return (0);
}
