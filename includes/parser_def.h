/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_def.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:02:26 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/06/09 13:02:26 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_DEF_H
# define PARSER_DEF_H

typedef struct s_ind_norm
{
	int	i;
	int	j;
	int	k;
	int	file_ind;
}t_ind_norm;

typedef struct s_two_strings
{
	char	*s;
	char	*r;
	char	**env;
	int		q;
}t_two_strings;

typedef struct s_token_parts
{
	char	**del;
	char	**file;
	char	*cmd;
	char	**cmd_arg;
}t_token_parts;

typedef struct s_token
{
	char			*token;
	t_token_parts	*tokens_parts;
	struct s_token	*next_token;
}	t_token;

t_token			*split_with_pipes(char **arg);
t_token			*parse_tokens(t_token *tokens, char **env);
t_token			*get_parts(t_token *tokens, int j, int *i);
t_token			*add_token(t_token *tokens, char *token);
t_token			*get_paths(char *path_v);
int				check_del(char *s);
int				check_quotes(char *arg, int i, char **s);
int				del_count(char *str);
char			*filter_space(char *str);
int				return_helper(char **arg, char **r, char **s, int j);
int				return_check(char *arg, int j);
int				first_pipe_check(char **arg);
t_token_parts	*init_parts(t_token *token);
char			**collect_red(t_token *tmp);
char			**collect_files(t_token *token, char **env);
char			*collect_cmd(t_token *token, char **env);
void			free_tokens(t_token **tokens);
int				file_maker(char *s, int j, char **r);
char			*setup_command(t_token_parts part, char **envp);
char			**filtered_args(char *cmd);
int				red_check(char *tmp);
void			init_strings(char **s, char **r);
void			free_strings(char **s, char **r);
int				rm_quotes(char *s, int i, t_two_strings *t_s);
void			cmd_helper(t_two_strings *t_s, t_token *token,
					t_ind_norm *ind_n);
int				skip_q(int i, char *s, char **ss);
int				skip_q_q(int i, char *s);
int				parser_helper_helper(char *s, int j);
int				allocc_size(char *s);
int				*del_indexes(char *s);
int				file_col_help(int j, t_token *token, t_two_strings *t_s);
int				red_col_help(int i, t_token *tmp, char **s);

#endif
