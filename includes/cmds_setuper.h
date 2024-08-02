/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_setuper.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:59:38 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/06/09 12:59:38 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_SETUPER_H
# define CMDS_SETUPER_H
# include "pipe_def.h"

char	**get_path(char **env);
int		prepare_cmd(char *s, int j, int k, t_two_strings *t_s);
char	**get_cmd(char **cmd, char **path);

#endif
