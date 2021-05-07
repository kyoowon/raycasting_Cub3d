/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 13:51:12 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/06 17:27:17 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

void init_DDA_wall(t_info *info, t_vec *vec, int x)
{
	vec->cameraX = 2 * x / (double)info->width - 1;
	vec->rayDirX = info->dirX + info->planeX * vec->cameraX;
	vec->rayDirY = info->dirY + info->planeY * vec->cameraX;
	vec->deltaDistX = fabs(1 / vec->rayDirX);
	vec->deltaDistY = fabs(1 / vec->rayDirY);
	vec->mapX = (int)info->posX;
	vec->mapY = (int)info->posY;
	if (vec->rayDirX < 0)
	{
		vec->stepX = -1;
		vec->sideDistX = (info->posX - vec->mapX) * vec->deltaDistX;
	}
	else
	{
		vec->stepX = 1;
		vec->sideDistX = (vec->mapX + 1.0 - info->posX) * vec->deltaDistX;
	}
	if (vec->rayDirY < 0)
	{
		vec->stepY = -1;
		vec->sideDistY = (info->posY - vec->mapY) * vec->deltaDistY;
	}
	else
	{
		vec->stepY = 1;
		vec->sideDistY = (vec->mapY + 1.0 - info->posY) * vec->deltaDistY;
	}
}

void is_DDA_hit(t_info *info, t_vec *vec)
{
	vec->hit = 0;
	while (vec->hit == 0)
	{
		if (vec->sideDistX < vec->sideDistY)
		{
			vec->sideDistX += vec->deltaDistX;
			vec->mapX += vec->stepX;
			vec->side = 0;
		}
		else
		{
			vec->sideDistY += vec->deltaDistY;
			vec->mapY += vec->stepY;
			vec->side = 1;
		}
		if (info->map.map[vec->mapX][vec->mapY] > 0)
			vec->hit = 1;
	}
}

void calc_wall(t_info *info, t_vec *vec)
{
	if (vec->side == 0)
		vec->perpWallDist = (vec->mapX - info->posX + (1 - vec->stepX) / 2) / vec->rayDirX;
	else
		vec->perpWallDist = (vec->mapY - info->posY + (1 - vec->stepY) / 2) / vec->rayDirY;
	vec->lineHeight = (int)(info->height / vec->perpWallDist);
	vec->drawStart = -vec->lineHeight / 2 + info->height / 2;
	if (vec->drawStart < 0)
		vec->drawStart = 0;
	vec->drawEnd = vec->lineHeight / 2 + info->height / 2;
	if (vec->drawEnd >= info->height)
		vec->drawEnd = info->height - 1;
}

void calc_texture(t_info *info, t_vec *vec, int x)
{
	int texNum;
	int texX;
	int texY;
	int color;
	double step;
	double texPos;
	int y;
	texNum = info->map.map[vec->mapX][vec->mapY] - 1;
	if (vec->side == 0)
		vec->wallX = info->posY + vec->perpWallDist * vec->rayDirY;
	else
		vec->wallX = info->posX + vec->perpWallDist * vec->rayDirX;
	vec->wallX -= floor(vec->wallX);
	texX = (int)(vec->wallX * (double)TEXWIDTH);
	if (vec->side == 0 && vec->rayDirX > 0)
		texX = TEXWIDTH - texX - 1;
	if (vec->side == 1 && vec->rayDirY < 0)
		texX = TEXWIDTH - texX - 1;
	step = 1.0 * TEXHEIGHT / vec->lineHeight;
	texPos = (vec->drawStart - info->height / 2 + vec->lineHeight / 2) * step;
	y = vec->drawStart;
	while(y < vec->drawEnd)
	{
		texY = (int)texPos & (TEXHEIGHT - 1);
		texPos += step;
		color = info->texture.texture[texNum][TEXHEIGHT * texY + texX];
		if (vec->side == 1)
			color = (color >> 1) & 8355711;
		info->texture.buf[y][x] = color;
		y++;
	}
}
void init_floor(t_vec *vec, t_floor *floor)
{
	floor->distWall = vec->perpWallDist;
	floor->distPlayer = 0.0;
	if (vec->side == 0 && vec->rayDirX > 0)
	{
		floor->floorXWall = vec->mapX;
		floor->floorYWall = vec->mapY + vec->wallX;
	}
	else if (vec->side == 0 && vec->rayDirX < 0)
	{
		floor->floorXWall = vec->mapX + 1.0;
		floor->floorYWall = vec->mapY + vec->wallX;
	}
	else if (vec->side == 1 && vec->rayDirY > 0)
	{
		floor->floorXWall = vec->mapX + vec->wallX;
		floor->floorYWall = vec->mapY;
	}
	else
	{
		floor->floorXWall = vec->mapX + vec->wallX;
		floor->floorYWall = vec->mapY + 1.0;
	}
}

void clac_floor(t_info *info, t_vec *vec, t_floor *floor, int x)
{
	int floorTexX;
	int floorTexY;
	int floorTexture;
	double weight;
	double currentFloorX;
	double currentFloorY;
	int checkerBoardPattern;
	int y;
	if (vec->drawEnd < 0)
		vec->drawEnd = info->height;
	y = vec->drawEnd + 1;
	while (y < info->height)
	{
		floor->currentDist = info->height / (2.0 * y - info->height);
		weight = (floor->currentDist - floor->distPlayer) / (floor->distWall - floor->distPlayer);
		currentFloorX = weight * floor->floorXWall + (1.0 - weight) * info->posX;
		currentFloorY = weight * floor->floorYWall + (1.0 - weight) * info->posY;
		floorTexX = (int)(currentFloorX * info->texture.texwidth) % info->texture.texwidth;
		floorTexY = (int)(currentFloorY * info->texture.texheight) % info->texture.texheight;
		checkerBoardPattern = ((int)(currentFloorX) + (int)(currentFloorY)) % 2;
		if (checkerBoardPattern == 0)
			floorTexture = 3;
		else
			floorTexture = 4;
		info->texture.buf[y][x] = (info->texture.texture[floorTexture][info->texture.texwidth * floorTexY + floorTexX] >> 1) & 8355711;
		info->texture.buf[info->height - y][x] = info->texture.texture[6][info->texture.texwidth * floorTexY + floorTexX];
		y++;
	}
}

void calc(t_info *info)
{
	int x;
	t_vec vec;
	t_floor floor;

	x = 0;
	while (x < info->width)
	{
		init_DDA_wall(info, &vec, x);
		is_DDA_hit(info, &vec);
		calc_wall(info, &vec);
		calc_texture(info, &vec, x);
		// verLine(info, x, drawStart, drawEnd, mapY, mapX, side);
		init_floor(&vec, &floor);
		clac_floor(info, &vec, &floor, x);
		x++;
	}
}