NAME	= libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

RM		= rm -f

SRCS = \
	ft_isascii.c ft_isprint.c ft_isalpha.c \
	ft_isdigit.c ft_isalnum.c ft_tolower.c \
	ft_toupper.c ft_strlen.c ft_strlcpy.c \
	ft_strlcat.c ft_strchr.c ft_strrchr.c \
	ft_strnstr.c ft_strncmp.c ft_atoi.c \
	ft_memset.c ft_bzero.c ft_memcpy.c \
	ft_memmove.c ft_memchr.c ft_memcmp.c \
	ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c \
	ft_itoa.c ft_substr.c ft_strjoin.c \
	ft_strtrim.c ft_split.c ft_strmapi.c \
	ft_strdup.c ft_calloc.c ft_striteri.c
OBJS = $(SRCS:.c=.o)

all:			$(NAME)

$(NAME):		$(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
