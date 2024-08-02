/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:21:42 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/08/16 15:00:36 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_exe_var
{
	int		rd;
	int		rw;
	int		j;
	int		**pfd;
	int		*id;
	char	**cmd;
}	t_var;

int		execution(t_token *tokens, char ***env);
int		is_builtin(char **cmd, char ***env, int fd);
int		exe_cmd(t_token *tokens, char ***env, t_var *var, int j);
char	**get_cmd_to_exe(char **s, char ***env);
void	waitchild(int *id, int j, int **pfd);
int		open_file_help(char *del, char *file, int fd);
void	ft_exit(char **cmd);
void	exe_helper_helper(t_var **var, int j);

#endif