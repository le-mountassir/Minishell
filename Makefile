# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/02 16:25:49 by ahel-mou          #+#    #+#              #
#    Updated: 2022/03/14 18:08:27 by ahel-mou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
FLAGS = -Wall -Wextra -Werror -lreadline

RL_DIR = $(addprefix $(shell brew --prefix readline), /)
LIB = minishell.h
RL = $(addprefix $(RL_DIR), $(LIB))

PARSER=	./src/parser/ft_split_utils.c \
		./src/parser/parse_cmd.c \
		./src/parser/check_quotes.c \
		./src/parser/split_rl_return.c \
		./src/parser/split_cmd_args.c \
		./src/parser/vars_lastretval.c \

EXEC =	./main.c \
		./src/exec/redirect_fds.c \
		./src/exec/pipe_line.c \
		./src/exec/pipe_utils_1.c \
		./src/exec/pipe_utils_2.c \
		./src/exec/here_doc.c \
		./src/exec/start_shell.c \
		

HOME_MADE =	./src/our_cmds/cd_cmd.c \
			./src/our_cmds/cd_tilde.c \
			./src/our_cmds/exit_cmd.c \
			./src/our_cmds/unset_cmd.c \
			./src/our_cmds/env_var_utils.c \
			./src/our_cmds/sort_env_var.c \
			./src/our_cmds/export_cmd/export_cmd.c \
			./src/our_cmds/export_cmd/export_utils.c \
			./src/our_cmds/export_cmd/split_export_cmd.c \
		
UTILS=	./src/utils/free_exit.c \
		./src/utils/reset.c \
		./src/utils/errors_handler.c \
		./src/utils/init_structures.c \
		./src/utils/str_utils.c \
		./src/utils/set_shell_levels.c \
		./src/utils/signals_handler.c \
		

OBJ = $(EXEC:.c=.o) $(PARSER:.c=.o) $(HOME_MADE:.c=.o) $(UTILS:.c=.o)

$(NAME): $(OBJ)
		echo -e "\033[0;33m"
		cd libft && make re
		$(CC) $(FLAGS) $(OBJ) ./libft/libft.a -o $(NAME)

all: $(NAME)

clean:
	find . -name "*.o" -delete

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re fcleanre
