/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 00:23:25 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/24 16:37:38 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUB3D_H
# define FT_CUB3D_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "key_press.h"
# include <math.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>

# define TEXWIDTH 64
# define TEXHEIGHT 64
# define uDiv 1
# define vDiv 1
# define vMove 10.0
# define ON 1
# define OFF 0

# define TITLE "cub3D"
# define EMPTY_LINE '\0'
# define EMPTY '0'
# define WALL '1'
# define SPRITE '2'

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3
# define SPR 4
# define FLOOR 5
# define CEILING 6
# define MAP_START -1

# define PI 3.1415926535897


typedef struct	s_img
{
	void		*img;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
	int			img_width;
	int			img_height;
}				t_img;

typedef struct	s_vec
{
	int			hit;
	int			mapX;
	int			mapY;
	int			side;
	int			stepX;
	int			stepY;
	double		perpWallDist;
	double		wallX;
	double		cameraX;
	double		rayDirX;
	double		rayDirY;
	double		sideDistX;
	double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
}				t_vec;

typedef struct	s_floor
{
	double floorXWall;
	double floorYWall;
	double distWall;
	double distPlayer;
	double currentDist;
}				t_floor;

typedef struct	s_texture
{
	char		*path[6];
	int			texture[6][TEXWIDTH * TEXHEIGHT];
	int			floor;
	int			ceiling;
}				t_texture;

typedef struct	s_map
{
	int			mapwidth;
	int			mapheight;
	char		**map;
}				t_map;

typedef struct	s_sprite
{
	double		x;
	double		y;
}				t_sprite;

typedef struct	s_player
{
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	double		moveSpeed;
	double		rotSpeed;
	char		dir;
}				t_player;

typedef struct	s_key
{
	int		key_a;
	int		key_w;
	int		key_s;
	int		key_d;
	int		key_ar_r;
	int		key_ar_l;
	int		key_esc;
}				t_key;

typedef struct	s_info
{
	void		*mlx;
	void		*win;
	int			fd;
	int			width;
	int			height;
	int			num_sprite;
	int			**buf;
	char		*line;
	double		*zBuffer;
	t_player	player;
	t_key		key;
	t_img		img;
	t_map		map;
	t_texture	texture;
	t_sprite	*sprite;
	t_list		*lstmap;
	int			*spriteOrder;
	double		*spriteDistance;
}				t_info;

typedef struct	s_pair
{
	double	first;
	int		second;
}				t_pair;

void	init_window(t_info *info);
void	init_info(t_info *info);
int		main_loop(t_info *info);
void	init_map(t_info *info);

void	calc(t_info *info);
void	draw(t_info *info);

int		rearrange_all(t_info *info);
void	apply_player_orientation(t_info *info);
void	allocate_buffer(t_info *info);
void	load_texture(t_info *info);
void	load_image(t_info *info, int *texture, char *path, t_img *img);

int		key_update(t_info *info);

void	validate_arguments(int argc, char *option, int *save);

void	open_cub(char *file_name, t_info *info);
void	open_cubfile(t_info *info);
int		decide_what_to_store(t_info *info, char **tab);
void	store_resolution(t_info *info, char *width, char *height);
void	store_texture(t_info *info, char *xpm_path, int flag);
void	store_color(t_info *info, char *rgb_with_comma, int flag);
void	validate_info(t_info *info);
void	read_map(t_info *info, char *line);
void	allocate_map(t_info *info, t_list *curr);
void	store_map_as_array(t_info *info, t_list *curr);
void	create_player(t_info *info, int i, int j);
void	validate_map(t_info *info);
void	validate_map_horizontal(char **map, int width, int height);
void	validate_map_vertical(char **map, int width, int height);
void	set_sprite(t_info *info);
void	rotate_player(t_player *player, double degree);
int		key_press(int key, t_info *info);
int		key_release(int key, t_info *info);
int     ft_bitmap(t_info *info);

#endif