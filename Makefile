# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/17 18:05:40 by kyuwonlee         #+#    #+#              #
#    Updated: 2021/05/27 01:50:38 by kyuwonlee        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D
CC		=	gcc
INCS	=	-I./srcs -I./libft -I./mlx
CFLAGS	=	-Wall -Werror -Wextra
INCLIB = -Lmlx -lmlx -framework OpenGL -framework Appkit -Llibft -lft

LIBFT_D = ./libft
LIBFT_A = ./libft/libft.a
MLX_D = ./mlx
MLX_A = ./mlx/libmlx.a

ABBR	=	ft_cub3d \
			ft_setting \
			ft_hook \
			ft_calc_screen \
			ft_validate_info \
			ft_read_info \
			ft_read_map \
			ft_save \
			ft_sprite \
			ft_wall \
			ft_read_info_sub

SRCS = $(addsuffix .c, $(addprefix srcs/, $(ABBR)))

OBJS	= $(SRCS:.c=.o)


all		: $(NAME)


$(NAME): $(OBJS)
	make -C $(LIBFT_D)
	make -C $(MLX_D)
	$(CC) $(CFLAGS) $(INCS) -o $(NAME) $(OBJS) $(INCLIB)

bonus: fclean $(B_OBJS)
	make -C $(LIBFT_D)
	$(CC) $(CFLAGS) $(INCS) -o $(BONUS) $(B_OBJS) $(INCLIB)

clean:
	make -C $(LIBFT_D) clean
	make -C $(MLX_D) clean
	rm -f $(OBJS) $(B_OBJS) *.bmp

fclean: clean
	rm -f $(NAME) $(BONUS) $(LIBFT_A) $(MLX_A)

re: fclean all

test: re
	./$(NAME) cubs/example.cub

.PHONY: bonus all clean fclean bonus re test save