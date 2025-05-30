NAME = libft.a
FLAG = -Wall -Wextra -Werror -g
SRC = ft_atoi.c		\
		ft_bzero.c		\
		ft_calloc.c		\
		ft_isalnum.c	\
		ft_isalpha.c	\
		ft_isascii.c	\
		ft_isdigit.c	\
		ft_isprint.c	\
		ft_putchar_fd.c	\
		ft_putendl_fd.c	\
		ft_putstr_fd.c	\
		ft_split.c		\
		ft_strchr.c		\
		ft_strdup.c		\
		ft_strjoin.c	\
		ft_strlen.c		\
		ft_strncmp.c	\
		ft_strrchr.c	\
		ft_strtrim.c	\
		ft_substr.c		\
		ft_memcpy.c		\
		ft_isspace.c	\
		ft_strlcpy.c	\
		ft_memset.c		\

OBJ = $(SRC:.c=.o)


all: $(NAME)

$(NAME):
	gcc $(FLAG) -c $(SRC)
	ar rc $(NAME) *.o
clean:
	/bin/rm -f  *.o
fclean: clean
	/bin/rm -f $(NAME)
re: fclean all

.PHONY: all bonus clean fclean re
