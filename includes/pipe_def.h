/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_def.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:00:18 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/06/09 13:00:18 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_DEF_H
# define PIPE_DEF_H
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct s_pipe
{
	int		fd[2];
	int		pi[2];
	int		pipes_num;
	char	*cmd;
	char	**path;
	char	**command;
	char	**command1;
	pid_t	*childs;
}t_pipe;

#endif
