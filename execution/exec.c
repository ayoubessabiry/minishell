/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:17:57 by aessabir          #+#    #+#             */
/*   Updated: 2022/08/19 18:20:16 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_file(char *del, char *file)
{
	int	fd;

	if (!ft_strcmp(del, "<"))
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd(RED"minshell : NO such file or directory\033[0m\n", 2);
			return (-1);
		}
	}
	if (!ft_strcmp(del, ">"))
	{
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd == -1)
		{
			ft_putstr_fd(RED"minishell : error while openning\033[0m\n", 2);
			return (-1);
		}
	}
	return (open_file_help(del, file, fd));
}

int	count_pipe(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		i++;
		token = token->next_token;
	}
	return (i);
}

char	**get_cmd_to_exe(char **s, char ***env)
{
	char	**cmd;
	char	**path;

	if (ft_strchr(s[0], '/') && access(s[0], F_OK) == 0)
		return (s);
	path = get_path(*env);
	if (!path)
		return (NULL);
	cmd = get_cmd(s, path);
	if (!(cmd))
		return (NULL);
	return (cmd);
}

int	exe_files(t_token_parts *token, t_var *var)
{
	int	i;

	i = 0;
	while (token->del[i])
	{
		if (var->rd && (!ft_strcmp(token->del[i], "<")
				|| !ft_strcmp(token->del[i], "<<")))
			close(var->rd);
		if (var->rw != 1 && (!ft_strcmp(token->del[i], ">")
				|| !ft_strcmp(token->del[i], ">>")))
			close(var->rw);
		if (!ft_strcmp(token->del[i], "<") || !ft_strcmp(token->del[i], "<<"))
			var->rd = open_file(token->del[i], token->file[i]);
		else
			var->rw = open_file(token->del[i], token->file[i]);
		if (var->rd == -1 || var->rw == -1)
			return (0);
		i++;
	}
	return (1);
}

int	execution(t_token *tokens, char ***env)
{
	int		j;
	t_var	var;

	j = 0;
	var.pfd = malloc(sizeof(int **) * count_pipe(tokens));
	var.id = malloc(sizeof(int *) * count_pipe(tokens));
	if (!var.pfd && !var.id)
		return (-1);
	while (tokens)
	{
		var.rw = 1;
		var.rd = 0;
		if (exe_files(tokens->tokens_parts, &var))
		{
			exe_cmd(tokens, env, &var, j);
			j++;
		}
		else if (j && !tokens->next_token)
			free(var.pfd[j - 1]);
		close_fd(&var.rd, &var.rw);
		tokens = tokens->next_token;
	}
	waitchild(var.id, j, var.pfd);
	return (0);
}
