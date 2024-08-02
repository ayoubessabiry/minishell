/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 07:58:28 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/06/19 07:58:28 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free(char ***s)
{
	int	i;

	i = 0;
	while ((*s)[i])
	{
		free((*s)[i]);
		i++;
	}
	if (*s)
		free(*s);
	*s = NULL;
}

void	free_tokens(t_token **tokens)
{
	t_token	*tmp;

	while ((*tokens))
	{
		tmp = *tokens;
		if (tmp->tokens_parts)
		{
			if (tmp->tokens_parts->del)
				ft_free (&tmp->tokens_parts->del);
			if (tmp->tokens_parts->file)
				ft_free (&tmp->tokens_parts->file);
			if (tmp->tokens_parts->cmd_arg)
				ft_free (&tmp->tokens_parts->cmd_arg);
			if (tmp->tokens_parts->cmd)
			{
				free(tmp->tokens_parts->cmd);
				tmp->tokens_parts->cmd = 0;
			}
			free(tmp->tokens_parts);
		}
		if (tmp->token)
			free(tmp->token);
		(*tokens) = (*tokens)->next_token;
		free(tmp);
	}
}
