/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 22:50:11 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/06/11 22:50:11 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef BUILTINS_H
# define BUILTINS_H
# define EXP    "export"
# define UNS    "unset"
# define ENV    "env"
# define PWD    "pwd"

void	pwd(char **env, int fd);
void	cd(char *path, char ***env);
void	echo(char **s, int fd);
void	envp(char ***env, int fd);
void	export(char ***env, char **s, int fd);
char	**get_env(char **s);
char	**unset(char **env, char **s);
int		check_builtin(t_token *tokens, char ***env, int rw, int j);
void	set_pwd(char ***env, char *pwd, int i);

#endif
