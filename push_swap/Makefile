# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erasahin <erasahin@student.42kocaeli.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/26 08:39:27 by erasahin          #+#    #+#              #
#    Updated: 2024/06/26 08:39:28 by erasahin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
FLAG = -Wall -Wextra -Werror
SRC = push_swap.c \
			function.c \
			function2.c \
			function3.c \
			rules_a.c \
			rules_b.c \
			utils.c

SRCO = $(SRC:.c=.o)

$(NAME): $(SRCO)
	gcc $(CFLAGS) $(SRCO) -o $(NAME)

all: $(NAME)

clean:
		@rm -f $(SRCO)

fclean: clean
		@rm -rf $(NAME)

re: fclean all

.phony: re fclean clean all
