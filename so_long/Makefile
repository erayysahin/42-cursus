# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erasahin <erasahin@student.42kocaeli.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/25 21:52:18 by erasahin          #+#    #+#              #
#    Updated: 2024/06/25 21:52:20 by erasahin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/main.c src/game.c src/map_constraction.c src/map_validation.c src/draw.c src/utils.c src/input.c src/path_finding.c
INC = inc
NAME = so_long
CC = gcc
CFLAGS = -Wall -Werror -Wextra
FRAMEWORKS = -framework OpenGL -framework AppKit
MLX = mlx/libmlx.a

all: $(NAME)

$(NAME): $(SRC) $(MLX)
	@gcc -g -o $(NAME) $(SRC) $(CFLAGS) $(FRAMEWORKS) $(MLX) -I $(INC)

$(MLX) :
			@make -C mlx

clean:
	@rm -rf $(NAME)

fclean: clean
	@make -C mlx clean

re: fclean all

.PHONY: clean fclean re all
