# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alexandr <alexandr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/15 18:38:45 by sjacki            #+#    #+#              #
#    Updated: 2021/10/15 07:42:08 by alexandr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

C_FILES			=		srcs/ft_philo.c		srcs/ft_utils.c		srcs/ft_atoi.c		srcs/ft_init_struct.c \
						srcs/ft_launch.c
						

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
	./$(NAME) 2 120 60 60