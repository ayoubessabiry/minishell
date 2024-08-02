/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 21:39:25 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/06/17 21:39:25 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

char	*expand(char *str, char **envp);
int		expand_fetcher(char *s, int j, t_two_strings *t_s);
int		exp_v(char c, int g);
void	exp_init(char **s, char *ss, int *g, int j);

#endif
