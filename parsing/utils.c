/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smounir <smounir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:16:08 by smounir           #+#    #+#             */
/*   Updated: 2022/05/30 15:16:08 by smounir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin(char *s1, char c)
{
	size_t	i;
	char	*joinedstring;

	i = 0;
	if (!s1)
		return (NULL);
	joinedstring = malloc(ft_strlen(s1) + 2);
	if (!joinedstring)
		return (0);
	joinedstring = ft_strcpy(joinedstring, s1);
	i = ft_strlen(joinedstring);
	joinedstring[i] = c;
	joinedstring[i + 1] = '\0';
	free(s1);
	return (joinedstring);
}

char	*ft_strjoin_str(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*joinedstring;

	j = 0;
	if (!s1 || !s2)
		return (NULL);
	joinedstring = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!joinedstring)
		return (0);
	joinedstring = ft_strcpy(joinedstring, s1);
	i = ft_strlen(joinedstring);
	while (s2[j])
		joinedstring[i++] = s2[j++];
	joinedstring[i] = '\0';
	free(s1);
	return (joinedstring);
}

t_token	*add_token(t_token *tokens, char *token)
{
	t_token	*n;
	t_token	*tmp;

	n = ft_calloc(1, sizeof(t_token));
	n->token = ft_strdup(token);
	n->next_token = 0;
	if (!tokens)
	{
		tokens = n;
		return (tokens);
	}
	tmp = tokens;
	while (tmp->next_token)
		tmp = tmp->next_token;
	tmp->next_token = n;
	return (tokens);
}
