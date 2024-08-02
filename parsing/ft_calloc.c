/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 05:00:34 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/07/26 05:00:34 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*b;

	i = 0;
	b = (unsigned char *)s;
	while (i < n)
		b[i++] = 0;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	p = malloc (size * count);
	if (!p)
		return (0);
	ft_bzero(p, size * count);
	return (p);
}
