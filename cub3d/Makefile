NAME	= cub3D

CC		= cc

RM		= rm -rf

CFLAGS	= -Wall -Wextra -Werror -g

SRC =	main.c \
		map_check/map_pars.c \
		map_check/map_check.c\
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c \
		exit.c \
		utils/utils.c \
		safe_allocation/s_malloc.c \
		safe_allocation/s_free.c \
		create_mlx.c \
		mlx_free.c \
		key.c \
		loop.c \
		raycas.c \
		rota.c \
		check_player.c \

LIBFT = libft/srcs/libft.a
MLX = minilibX/libmlx.a
MLXFLAG = -Imlx_linux -lXext -lX11 -lm -lz
 
OBJ_DIR = .objs

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all : $(NAME)

$(NAME): $(MLX) $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(MLX) $(MLXFLAG)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(@D)
	@echo -e "\033[2J\033[H"
	@echo "\033[1;32mCompiling : \033[1;34m$<\033[0m"
	@sleep 0.01
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C libft/srcs

$(MLX):
	@$(MAKE) -C minilibX

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C libft/srcs clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C libft/srcs fclean
	@$(MAKE) -C minilibX clean
re: fclean all


.PHONY: all fclean clean re