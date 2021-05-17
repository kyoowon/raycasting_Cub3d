/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 00:23:25 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/17 17:54:59 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "key_press.h"
# include <math.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>

# define MAPWIDTH 24
# define MAPHEIGHT 24
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define numSprites 19
# define uDiv 1
# define vDiv 1
# define vMove 0.0

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
	int			**buf;
	int			**texture;
	int			texheight;
	int			texwidth;
}				t_texture;

typedef struct	s_map
{
	int			mapwidth;
	int			mapheight;
	int			map[MAPWIDTH][MAPHEIGHT];
}				t_map;

typedef struct	s_sprite
{
	double		x;
	double		y;
	int			texture;
}				t_sprite;

typedef struct	s_info
{
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	double		moveSpeed;
	double		rotSpeed;
	double		*zBuffer;
	t_img		img;
	t_map		map;
	t_texture	texture;
	t_sprite	sprite[numSprites];
	int			spriteOrder[numSprites];
	double		spriteDistance[numSprites];
	int key_a;
	int key_w;
	int key_s;
	int key_d;
	int key_esc;
}				t_info;

typedef struct	s_pair
{
	double	first;
	int		second;
}				t_pair;


void	calc(t_info *info);
void	verLine(t_info *info, int x, int winy1, int winy2, int mapY, int mapX, int side);
void	draw(t_info *info);
int		init_texture(t_info *info);
void	draw_texture(t_info *info);
void	load_texture(t_info *info);
void	load_image(t_info *info, int *texture, char *path, t_img *img);
void	key_update(t_info *info);
int		key_press(int key, t_info *info);
int		key_release(int key, t_info *info);

#endif