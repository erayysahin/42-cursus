# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erasahin <erasahin@student.42kocaeli.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/28 21:50:14 by erasahin          #+#    #+#              #
#    Updated: 2024/06/28 22:59:46 by erasahin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
LIBFT = libft
SRCS = server.c client.c
all: $(NAME)

$(NAME): $(LIBFT) $(SRCS)
		make -C $(LIBFT)
		cp libft/libft.a .
		gcc server.c $(NAME) -o server
		gcc client.c $(NAME) -o client
clean:
		make clean -C $(LIBFT)
fclean: clean
		make fclean -C $(LIBFT)
		rm -rf $(NAME)
		rm -rf server client
re : fclean all
.PHONY: clean fclean all re