# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 10:56:05 by ahel-mou          #+#    #+#              #
#    Updated: 2022/03/25 17:01:25 by ahel-mou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INC = libft.h

SRC	=	ft_strlen.c\
		ft_numlen.c\
		td_arr_len.c\
		ft_strcmp.c\
		ft_strncmp.c\
		ft_strncpy.c\
		ft_strlcpy.c\
		ft_strcat.c	\
		ft_strlcat.c\
		ft_strdup.c	\
		ft_substr.c	\
		ft_join.c\
		ft_split.c\
		ft_space.c\
		ft_putstr_fd.c\
		ft_isalpha.c\
		ft_isnumber.c\
		ft_isdigit.c\
		ft_isalnum.c\
		ft_atoi.c\
		ft_itoa.c\
		ft_intlen.c\
		ft_strchr.c\
		ft_memset.c\
		ft_intlen.c\
		ft_splitpath.c\
		ft_strjoin.c\
		ft_putnbr_fd.c\
		ft_isprint.c\
		
OBJS = $(SRC:%.c=%.o)

NAME = libft.a

CC = gcc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

$(NAME): $(SRC)
	@$(CC) $(CFLAGS) -c $(SRC)
	@ar rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
	@$(RM) $(OBJS) $(OBJB)

fclean: clean
		@$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all
