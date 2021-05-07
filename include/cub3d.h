/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 00:23:25 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/06 22:07:27 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "../mlx/mlx.h"
#include "../libft/libft.h"
#include "key_press.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

# define MAPWIDTH 24
# define MAPHEIGHT 24
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define numSprites 19


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
}				t_info;

// struct			Sprite
// {
// 	double		x;
// 	double		y;
// 	int			texture;
// };

// Sprite	sprite[numSprites] =
// {
// 	{20.5, 11.5, 10}, //green light in front of playerstart
// 	//green lights in every room
// 	{18.5,4.5, 10},
// 	{10.0,4.5, 10},
// 	{10.0,12.5,10},
// 	{3.5, 6.5, 10},
// 	{3.5, 20.5,10},
// 	{3.5, 14.5,10},
// 	{14.5,20.5,10},

// 	//row of pillars in front of wall: fisheye test
// 	{18.5, 10.5, 9},
// 	{18.5, 11.5, 9},
// 	{18.5, 12.5, 9},

// 	//some barrels around the map
// 	{21.5, 1.5, 8},
// 	{15.5, 1.5, 8},
// 	{16.0, 1.8, 8},
// 	{16.2, 1.2, 8},
// 	{3.5,  2.5, 8},
// 	{9.5, 15.5, 8},
// 	{10.0, 15.1,8},
// 	{10.5, 15.8,8},
// };

// typedef struct		s_pair
// {
// 	double	first;
// 	int		second;
// }					t_pair;


// int		spriteOrder[numSprites];
// double	spriteDistance[numSprites];


void	calc(t_info *info);
void	verLine(t_info *info, int x, int winy1, int winy2, int mapY, int mapX, int side);
void	draw(t_info *info);
int		init_texture(t_info *info);
void	draw_texture(t_info *info);
void	load_texture(t_info *info);
void	load_image(t_info *info, int *texture, char *path, t_img *img);
int		key_press(int key, t_info *info);

#endif