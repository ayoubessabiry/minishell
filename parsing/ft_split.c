/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:10:59 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/07/04 13:32:59 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	i;
	char	*duplicate;

	i = 0;
	duplicate = malloc(n + 1);
	if (!duplicate)
		return (NULL);
	while (s1[i] && i < n)
	{
		duplicate[i] = s1[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}

int	ft_word_count(const char *s, char charset)
{
	size_t	i;
	size_t	j;
	int		length;

	length = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != charset)
		{
			j = i;
			while (s[j] && s[j] != charset)
				j++;
			length++;
			i = j - 1;
		}
		i++;
	}
	return (length + 1);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	size_t	i;
	size_t	j;
	size_t	stringindex;

	if (!s)
		return (0);
	words = malloc(sizeof(char *) * ft_word_count(s, c));
	if (!words)
		return (0);
	stringindex = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] != c)
		{
			j = i;
			while (s[j] != c && s[j])
				j++;
			words[stringindex++] = ft_strndup(&s[i], j - i);
			i = j - 1;
		}
	}
	words[stringindex] = 0;
	return (words);
}
