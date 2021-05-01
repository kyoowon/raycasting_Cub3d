# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/17 18:05:40 by kyuwonlee         #+#    #+#              #
#    Updated: 2021/04/30 23:22:03 by kyuwonlee        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	a.out
SRCS	=	main.c
CC		=	clang
CFLAGS	=	-Wall -Werror -Wextra
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