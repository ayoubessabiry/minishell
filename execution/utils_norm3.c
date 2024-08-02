/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_norm3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 16:37:45 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/08/19 19:59:20 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_op(char *s)
{
	int	i;

	i = 0;
	if (s[i] != '-' || (s[i] == '-' && s[i + 1] != 'n'))
		return (0);
	while (s[++i])
	{
		if (s[i] != 'n')
			return (0);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int			i;
	long long	n;
	int			sign;

	i = 0;
	n = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - 48);
		i++;
	}
	return (n * sign);
}

int	ft_isdigit(char *c)
{
	int	i;

	i = -1;
	while (c[++i])
	{
		if (c[i] < '0' || c[i] > '9')
			return (0);
	}
	return (1);
}

void	ft_exit(char **cmd)
{
	if (cmd[0] && ft_isdigit(cmd[0]))
	{
		if (cmd[1])
		{
			ft_putstr_fd(RED"Minishell: exit: too many arguments\033[0m\n", 2);
			g_status = 1;
			return ;
		}
		else
			g_status = ft_atoi(cmd[0]);
	}
	else if (cmd[0])
	{
		ft_putstr_fd(RED"Minishell: exit: numeric argument required\033[0m\n",
			2);
		g_status = 1;
	}
	exit(g_status);
}

void	waitchild(int *id, int j, int **pfd)
{
	int	i;
	int	ind;
	int	res;

	ind = 0;
	i = 0;
	res = 0;
	while (ind < j && res != -1)
	{
		res = waitpid(id[ind++], &i, 0);
		if (res == id[j - 1])
		{
			g_status = WEXITSTATUS(i);
			if (WIFSIGNALED(i))
			{
				if (WTERMSIG(i) == SIGQUIT)
					printf("QUIT: %d\n", WTERMSIG(i));
				g_status = 128 + WTERMSIG(i);
			}
		}
	}
	free(id);
	free(pfd);
}
