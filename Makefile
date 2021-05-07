# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/17 18:05:40 by kyuwonlee         #+#    #+#              #
#    Updated: 2021/05/07 19:05:02 by kyuwonlee        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	a.cub
SRCS	=	ft_cub3d.c \
			ft_drawing.c \
			ft_hook.c \
			ft_parsing.c
CC		=	clang
HEAD	= 	./include
CFLAGS	=	-Wall -Werror -Wextra
CLIB	=	-lmlx -framework OpenGL -framework Appkit -Imlx

OBJS	= $(SRCS:.c=.o)

.c.o :
	$(CC) $(CFLAGS) -I ./mlx -I $(HEAD) -c $< -o $@


all		: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -L ./mlx -L ./libft $(CLIB) $(OBJS) -o $(NAME)
	install_name_tool -change libmlx.dylib ./mlx/libmlx.dylib $(NAME)

clean	:
	rm -rf $(OBJS)

fclean	: clean
	rm -rf	$(NAME)

re		: fclean all