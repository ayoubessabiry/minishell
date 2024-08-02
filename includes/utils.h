/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:55:32 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/06/09 12:55:32 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include "parser_def.h"

size_t	ft_strlen(const char *str);
void	ft_putstr_fd(char *s, int fd);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strjoin(char *s1, char c);
char	*skip_s(char *s);
char	*ft_strjoin_str(char *s1, char *s2);
char	*ft_strndup(const char *s1, size_t n);
char	**ft_split(char const *s, char c);
int		is_valid_del(char del);
char	*lower(char *str);
int		is_space(char c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(char *s1);
void	ft_free(char ***s);
void	change_oldpwd(char ***env);
void	change_env(char ***env, char *s, char *new);
void	compose_three_lines(char ***s, int i, char ***env);
char	*ft_strchr(const char *s, int c);
char	**ft_realoc(char **env, char *s);
int		check_def(char ***env, char *s);
int		count_word(char **s);
void	ft_close(t_token *tokens, int **pfd, int j);
void	close_fd(int *rd, int *rw);
int		skip(char *str, char c);
char	*ft_itoa(int n);
void	*ft_calloc(size_t count, size_t size);
void	init_strings(char **s, char **r);
void	free_strings(char **s, char **r);
int		skip_space(int j, char *s, int *q);
int		check_op(char *s);
int		ft_isdigit(char *c);
int		check_ide(char *s);

#endif
