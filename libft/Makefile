# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahel-mou <ahel-mou@1337.ma>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/02 14:18:36 by ahel-mou          #+#    #+#              #
#    Updated: 2022/02/21 12:53:59 by ahel-mou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c\
	  ft_isascii.c ft_isdigit.c ft_isprint.c ft_memcpy.c\
	  ft_memchr.c ft_memmove.c ft_memset.c ft_memcmp.c\
	  ft_strchr.c ft_strrchr.c ft_strdup.c ft_strlcat.c\
	  ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strrchr.c\
	  ft_tolower.c ft_toupper.c ft_strnstr.c ft_substr.c\
	  ft_strjoin.c ft_calloc.c ft_strtrim.c ft_split.c\
	  ft_putchar_fd.c ft_putnbr_fd.c ft_putendl_fd.c\
	  ft_putstr_fd.c ft_itoa.c ft_strrev.c ft_strmapi.c ft_striteri.c ft_strcmp.c

CC = cc

FLAGS = -Wall -Werror -Wextra

OBJS = $(SRCS:.c=.o)
B_OBJS = $(B_SRC:.c=.o)

all: $(NAME)


$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(FLAG) -c $<

clean:
	find . -name "*.o" -delete

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean, fclean, all, re