# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/02 16:25:49 by ahel-mou          #+#    #+#              #
#    Updated: 2022/03/21 13:55:55 by ahel-mou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
FLAGS = -Wall -Wextra -Werror 

# -I
RL_INCLUDE = $(addprefix $(shell brew --prefix readline), /include)
# -L
RL_LIB = $(addprefix $(shell brew --prefix readline), /lib)
LIB = minishell.h

PARSER=	./parser/parse_cmd.c \
		./parser/check_quotes.c \
		./parser/split_rl_return.c \
		./parser/split_cmd_args.c \
		./parser/vars_lastretval.c \

EXEC =	./main.c \
		./exec/redirect_fds.c \
		./exec/execution.c \
		./exec/here_doc.c \
		./exec/start_shell.c \
		

HOME_MADE =	./our_cmds/cd_cmd.c \
			./our_cmds/cd_tilde.c \
			./our_cmds/exit_cmd.c \
			./our_cmds/unset_cmd.c \
			./our_cmds/echo_cmd.c\
			./our_cmds/env_var_utils.c \
			./our_cmds/sort_env_var.c \
			./our_cmds/export_cmd/export_cmd.c \
			./our_cmds/export_cmd/export_utils.c \
			./our_cmds/export_cmd/split_export_cmd.c \
		
UTILS=	./utils/free_exit.c \
		./utils/reset.c \
		./utils/errors_handler.c \
		./utils/init_structures.c \
		./utils/utils_1.c \
		./utils/utils_2.c \
		./utils/utils_3.c \

		

OBJ = $(EXEC:.c=.o) $(PARSER:.c=.o) $(HOME_MADE:.c=.o) $(UTILS:.c=.o)


$(NAME): $(OBJ)
		cd libft && make re
		$(CC) $(FLAGS) $(OBJ) -L $(RL_LIB) -lreadline ./libft/libft.a -o $(NAME)

%.o:%.c minishell.h
	$(CC) $(FLAGS) -c $< -o $@ -I $(RL_INCLUDE)
	
all: $(NAME)

clean:
	find . -name "*.o" -delete

fclean: clean
	rm -f $(NAME)
	rm -f ./libft/libft.a

re:	fclean all

.PHONY: all clean fclean re fcleanre
