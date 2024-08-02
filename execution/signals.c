/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 01:37:33 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/08/14 22:07:49 by smounir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_file_help(char *del, char *file, int fd)
{
	if (!ft_strcmp(del, ">>"))
	{
		fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd == -1)
		{
			ft_putstr_fd(RED"minishell: error while openning\033[0m\n", 2);
			return (-1);
		}
	}
	if (!ft_strcmp(del, "<<"))
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd(RED"minishell: error while openning\033[0m\n", 2);
			return (-1);
		}
	}
	return (fd);
}

void	envp(char ***env, int fd)
{
	int		i;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strchr((*env)[i], '='))
		{
			ft_putstr_fd((*env)[i], fd);
			ft_putstr_fd("\n", fd);
		}
		i++;
	}
	g_status = 0;
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	signal_handle(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 1;
	}
}

void	interrupt(void)
{
	signal(SIGINT, signal_handle);
	signal(SIGQUIT, SIG_IGN);
}
