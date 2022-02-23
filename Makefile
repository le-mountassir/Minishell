# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/18 21:31:37 by ahel-mou          #+#    #+#              #
#    Updated: 2022/02/23 17:03:15 by ahel-mou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -Wall -Werror -Wextra -l readline

#----------------------------------> minishell utils
SRC_mini = minishell.c\
			./exec/exec_cmds.c\
			./exec/find_path.c\
			./exec/home_made_cmd.c\

#----------------------------------> Parsing
SRC_parser = ./parsing/handle_input.c\
				./parsing/parsing_utils.c

#----------------------------------> commands src files
SRC_commands = ./commands/ft_cd.c\
				./commands/ft_echo.c\
				./commands/ft_env.c\
				./commands/ft_pwd.c\
				./commands/ft_exit.c\
				./commands/ft_unset.c\
				./commands/var_env.c\
				./commands/ft_export.c\

OBJ = $(SRC_mini:.c=.o) $(SRC_libft:.c=.o) $(SRC_commands:.c=.o) $(SRC_parser:.c=.o)

HEADER = ./minishell.h

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
		cd libft && make
		$(CC) $(FLAGS) $(OBJ) ./libft/libft.a -o $(NAME)
		clear && ./$(NAME)

clean:
	find . -name "*.o" -delete

fclean: clean
	rm -f $(NAME)
	rm -f ./libft/libft.a

re: fclean all

.PHONY: all clean fclean re
