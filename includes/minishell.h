/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brogrammerz <brogrammerz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:07:03 by brogrammerz       #+#    #+#             */
/*   Updated: 2022/05/21 14:07:03 by brogrammerz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <string.h>
# include <fcntl.h>
# include "signals.h"
# include "utils.h"
# include "cmds_setuper.h"
# include "parser_def.h"
# include "builtins.h"
# include "expand.h"
# include "heredoc.h"
# include "execution.h"
# define RESET "\033[0m"
# define RED "\033[31m" 
# define PATH "PATH="

int	g_status;

#endif
