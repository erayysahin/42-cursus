# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erasahin <@student.42kocaeli.com.tr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/06 13:09:29 by erasahin          #+#    #+#              #
#    Updated: 2024/02/08 14:25:27 by erasahin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a

SRCS	=	ft_printf.c ft_printf.utils.c

OBJS = $(SRCS:.c=.o)


CC	=	gcc
RM	=	rm -rf
//FLAGS	= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): 
		$(CC) $(FLAGS) -c $(SRCS) 
		ar rc $(NAME) $(OBJS)

clean:
		$(RM) $(OBJS) 

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re