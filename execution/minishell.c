/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smounir <smounir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:07:26 by smounir           #+#    #+#             */
/*   Updated: 2022/08/14 22:06:49 by smounir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin_2(char **cmd, char ***env, int fd)
{
	if (!ft_strcmp("env", cmd[0]))
	{
		envp(env, fd);
		return (1);
	}
	if (!ft_strcmp("cd", cmd[0]))
	{
		cd(cmd[1], env);
		return (1);
	}
	if (!ft_strcmp("pwd", cmd[0]))
	{
		pwd(*env, fd);
		return (1);
	}
	if (!ft_strcmp("exit", cmd[0]))
	{
		ft_putstr_fd("exit", fd);
		ft_putstr_fd("\n", fd);
		ft_exit(cmd + 1);
		return (1);
	}
	return (0);
}

int	is_builtin(char **cmd, char ***env, int fd)
{
	if (!ft_strcmp("echo", cmd[0]))
	{
		echo(cmd + 1, fd);
		return (1);
	}
	if (!ft_strcmp("export", cmd[0]))
	{
		export(env, cmd + 1, fd);
		return (1);
	}
	if (!ft_strcmp("unset", cmd[0]))
	{
		*env = unset(*env, cmd);
		return (1);
	}
	return (is_builtin_2(cmd, env, fd));
}

int	all_space(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (!is_space(str[i]))
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

void	minishell(t_token **tokens, char **str, char ***our_env)
{
	while (1)
	{
		interrupt();
		*str = readline("minishell> ");
		if (!*str)
		{
			printf("exit\n");
			break ;
		}
		if ((*str)[0] != '\0')
			add_history(*str);
		if (*str && !all_space(*str) && red_check(*str))
		{
			*tokens = split_with_pipes(str);
			*tokens = parse_tokens(*tokens, *our_env);
			heredoc_check(*tokens, *our_env);
			execution(*tokens, our_env);
			if (*tokens)
				free_tokens(tokens);
			free(*str);
			*str = 0;
		}
		else
			free(*str);
	}
}

int	main(int ac, char **av, char **env)
{
	char		**our_env;
	char		*str;
	t_token		*tokens;

	(void)ac;
	(void)av;
	str = 0;
	tokens = 0;
	our_env = get_env(env);
	minishell(&tokens, &str, &our_env);
	ft_free(&our_env);
	return (g_status);
}
