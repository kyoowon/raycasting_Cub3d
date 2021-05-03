# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/17 18:05:40 by kyuwonlee         #+#    #+#              #
#    Updated: 2021/05/02 15:17:04 by kyuwonlee        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	a.out
SRCS	=	cub3d.c
CC		=	clang
HEAD	=	cub3d.h \
			key_press.h
CFLAGS	=	-Wall -Werror -Wextra -I .
CLIB	=	-lmlx -framework OpenGL -framework Appkit -Imlx

OBJS	= $(SRCS:.c=.o)

.c.o :
	$(CC) $(CFLAGS) -I ./mlx -c $< -o $@


all		: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -L ./mlx $(CLIB) $(OBJS) -o $(NAME)
	install_name_tool -change libmlx.dylib ./mlx/libmlx.dylib $(NAME)

clean	:
	rm -rf $(OBJS)

fclean	: clean
	rm -rf	$(NAME)

re		: fclean all