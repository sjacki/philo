# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sjacki <sjacki@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/15 18:38:45 by sjacki            #+#    #+#              #
#    Updated: 2021/09/28 22:10:38 by sjacki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

C_FILES			=		srcs/philo.c	srcs/utils.c	srcs/ft_atoi.c	srcs/init_struct.c \
						srcs/launch.c
						

O_FILES = $(C_FILES:.c=.o)

HEADER = header/philo.h

.PHONY: all bonus clean fclean re

all: $(NAME)

$(NAME): $(O_FILES)
	gcc -g -Wall -Wextra -Werror $(O_FILES) -o $(NAME)

%.o: %.c $(HEADER)
	gcc -c $<

clean:
	rm -f $(O_FILES)

fclean: clean
	rm -f $(NAME)

bonus: re

re: fclean all

run: all
	clear
	./$(NAME) 5 60 60 60