CC= gcc -Wall -Wextra -Werror -I /goinfre/${USER}/homebrew/opt/readline/include
SRC=execution/builtins.c\
	execution/minishell.c\
	execution/utils_norm3.c\
	execution/utils_norm4.c\
	execution/utils_norm5.c\
	execution/signals_helper.c\
	execution/exec.c\
	execution/utils_norm2.c\
	execution/builtins_norm.c\
	execution/signals.c\
	execution/exec_norm.c\
	parsing/parser.c\
	parsing/utils.c\
	parsing/utils_norm.c\
	parsing/utils_norm_2.c\
	parsing/ft_split.c\
	parsing/help_parse.c\
	parsing/parser_helper.c\
	parsing/error_returns.c\
	parsing/ft_itoa.c\
	parsing/ft_calloc.c\
	parsing/two_strings.c\
	parsing/expand.c\
	parsing/token_parts_manager.c\
	parsing/manager_helper.c\
	parsing/manager_helper_2.c\
	parsing/heredoc.c\
	parsing/heredoc_helper.c\
	parsing/clean_memory.c\
	parsing/check_cmd_quotes.c\
	parsing/parts_manager_return_error.c
OBJ= $(SRC:.c=.o)
NAME= minishell

all: $(NAME)

$(NAME):$(OBJ)
	$(CC) -o $(NAME) $(OBJ) -lreadline -L /goinfre/${USER}/homebrew/opt/readline/lib
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all
