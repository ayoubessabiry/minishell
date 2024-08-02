/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:23:35 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/06/20 19:23:35 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "../includes/minishell.h"

void	heredoc(char *delimiter, char **env);
void	heredoc_check(t_token *tokens, char **env);
t_token	*heredoc_files_setter(t_token *tmp, t_token *tokens);
t_token	*create_file_names(t_token *tokens);
int		heredoc_signal_init(t_token *tokens, int pid);
void	heredoc_signal_parent(int pid, t_token *tmp, t_token *tokens);

#endif
