/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:45:46 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/06/25 15:45:46 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	alloc_size(char *cmd)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		j = i;
		while (cmd[j] && is_space(cmd[j]))
			j++;
		if (cmd[j] != '"' && cmd[j] != '\'')
		{
			while (cmd[j] && !is_space(cmd[j])
				&& cmd[j] != '"' && cmd[j] != '\'')
				j++;
			count++;
		}
		while (cmd[j] && (cmd[j] == '"' || cmd[j] == '\''))
			j++;
		i = j;
	}
	return (count + 1);
}

int	helper(int ind, char **cmd, char ***args, int *j)
{
	while ((*cmd)[*j] && !is_space((*cmd)[*j])
		&& (*cmd)[*j] != '"' && (*cmd)[*j] != '\'')
			(*args)[ind] = ft_strjoin((*args)[ind], (*cmd)[(*j)++]);
	if (ind == 0 && (*args)[ind][0] != '$')
		(*args)[ind] = lower((*args)[ind]);
	if (is_space((*cmd)[*j]))
	{
		ind++;
		(*args)[ind] = ft_strdup("");
	}
	if (!(*cmd)[*j])
		ind++;
	return (ind);
}

int	helper2(int ind, char **cmd, char ***args, int *j)
{
	if ((*cmd)[*j] == '"')
	{
		(*j)++;
		while ((*cmd)[*j] && (*cmd)[*j] != '"')
			(*args)[ind] = ft_strjoin((*args)[ind], (*cmd)[(*j)++]);
	}
	if ((*cmd)[*j] == '\'')
	{
		(*j)++;
		while ((*cmd)[*j] && (*cmd)[*j] != '\'')
			(*args)[ind] = ft_strjoin((*args)[ind], (*cmd)[(*j)++]);
	}
	(*j)++;
	if (is_space((*cmd)[*j]))
	{
		ind++;
		(*args)[ind] = ft_strdup("");
	}
	if (!(*cmd)[*j])
		ind++;
	return (ind);
}

char	**filtered_args(char *cmd)
{
	char	**args;
	int		ind;
	int		i;
	int		j;

	ind = 0;
	i = 0;
	if (!cmd[0])
		return (0);
	args = malloc(sizeof(char *) * (alloc_size(cmd) + 10));
	args[ind] = ft_strdup("");
	while (cmd[i])
	{
		j = i;
		while (cmd[j] && is_space(cmd[j]))
			j++;
		if (cmd[j] != '"' && cmd[j] != '\'')
			ind = helper(ind, &cmd, &args, &j);
		else
			ind = helper2(ind, &cmd, &args, &j);
		i = j;
	}
	args[ind] = 0;
	return (args);
}
