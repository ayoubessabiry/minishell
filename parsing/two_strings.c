/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_strings.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 22:42:03 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/07/26 22:42:03 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_strings(char **s, char **r)
{
	*s = ft_strdup("");
	*r = ft_strdup("");
}

void	free_strings(char **s, char **r)
{
	free(*r);
	free(*s);
}
