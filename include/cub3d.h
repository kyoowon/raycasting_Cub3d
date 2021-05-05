/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 00:23:25 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/05 14:46:47 by kyuwonlee        ###   ########.fr       */
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

/*
** void		*mlx
** void		*win  : 새로운 윈도우 식별자
** int		width : 윈도우 폭
** int		height: 윈도우 높이
** double	posX  : 초기 사용자의 x 위치벡터
** double	posY  : 초기 사용자의 y 위치벡터
** double	dirX  : 플레이어의 x 방향벡터
** double	dirY  : 플레이어의 y 방향벡터
** double	planeX: 카메라 x 평면벡터
** double	planeY: 카메라 y 평면벡터
** double	moveSpeed;
** double	rotSpeed;
*/

# define MAPWIDTH 24
# define MAPHEIGHT 24
# define TEXWIDTH 64
# define TEXHEIGHT 64

typedef struct	s_img
{
	void	*img;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct	s_vec
{
		int hit;
		int mapX;
		int mapY;
		int side;
		int stepX;
		int stepY;
		double perpWallDist;
		double wallX;
		double cameraX;
		double rayDirX;
		double rayDirY;
		double sideDistX;
		double sideDistY;
		double deltaDistX;
		double deltaDistY;
}				t_vec;

typedef struct	s_info
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	moveSpeed;
	double	rotSpeed;
	int		**buf;
	int		mapwidth;
	int		mapheight;
	int		texheight;
	int		texwidth;
	int		**texture;
	int		map[MAPWIDTH][MAPHEIGHT];
	t_img	img;
}				t_info;

void	calc(t_info *info);
void	verLine(t_info *info, int x, int winy1, int winy2, int mapY, int mapX, int side);
void	draw(t_info *info);
int		init_texture(t_info *info);
void	draw_texture(t_info *info);
void	load_texture(t_info *info);
void	load_image(t_info *info, int *texture, char *path, t_img *img);
int		key_press(int key, t_info *info);

#endif