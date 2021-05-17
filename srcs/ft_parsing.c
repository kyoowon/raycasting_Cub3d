/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 13:51:12 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/17 17:51:46 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void sort_order(t_pair *orders, int amount)
{
	t_pair tmp;
	int i;
	int j;

	i = 0;
	while (i < amount)
	{
		j = 0;
		while (j < amount - 1)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
			j++;
		}
		i++;
	}
}

void sortSprites(int *order, double *dist, int amount)
{
	t_pair *sprites;
	int i;

	sprites = (t_pair *)malloc(sizeof(t_pair) * amount);
	i = 0;
	while (i < amount)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
		i++;
	}
	sort_order(sprites, amount);
	i = 0;
	while (i < amount)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
		i++;
	}
	free(sprites);
}

void draw_floor(t_info *info)
{
	int x;
	int y;

	y = info->height / 2 + 1;
	while (y < info->height)
	{
		float rayDirX0 = info->dirX - info->planeX;
		float rayDirY0 = info->dirY - info->planeY;
		float rayDirX1 = info->dirX + info->planeX;
		float rayDirY1 = info->dirY + info->planeY;
		int p = y - info->height / 2;
		float posZ = 0.5 * info->height;
		float rowDistance = posZ / p;
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / info->width;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / info->width;
		float floorX = info->posX + rowDistance * rayDirX0;
		float floorY = info->posY + rowDistance * rayDirY0;
		x = 0;
		while (++x < info->width)
		{
			int cellX = (int)(floorX);
			int cellY = (int)(floorY);
			int tx = (int)(info->texture.texwidth * (floorX - cellX)) & (info->texture.texwidth - 1);
			int ty = (int)(info->texture.texheight * (floorY - cellY)) & (info->texture.texheight - 1);
			floorX += floorStepX;
			floorY += floorStepY;
			int checkerBoardPattern = (int)(cellX + cellY) & 1;
			int floorTexture;
			if (checkerBoardPattern == 0)
				floorTexture = 3;
			else
				floorTexture = 4;
			int ceilingTexture = 6;
			int color;
			color = info->texture.texture[floorTexture][info->texture.texwidth * ty + tx];
			color = (color >> 1) & 8355711;
			info->texture.buf[y][x] = color;
			color = info->texture.texture[ceilingTexture][info->texture.texwidth * ty + tx];
			color = (color >> 1) & 8355711;
			info->texture.buf[info->height - y - 1][x] = color;
		}
		y++;
	}
}

void draw_wall(t_info *info, t_vec *vec)
{
	int x;
	int y;

	x = 0;
	while (x < info->width)
	{
		vec->cameraX = 2 * x / (double)info->width - 1;
		vec->rayDirX = info->dirX + info->planeX * vec->cameraX;
		vec->rayDirY = info->dirY + info->planeY * vec->cameraX;
		vec->mapX = (int)info->posX;
		vec->mapY = (int)info->posY;
		vec->deltaDistX = fabs(1 / vec->rayDirX);
		vec->deltaDistY = fabs(1 / vec->rayDirY);
		vec->hit = 0;
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
		int texNum = info->map.map[vec->mapX][vec->mapY] - 1;
		if (vec->side == 0)
			vec->wallX = info->posY + vec->perpWallDist * vec->rayDirY;
		else
			vec->wallX = info->posX + vec->perpWallDist * vec->rayDirX;
		vec->wallX -= floor((vec->wallX));
		int texX = (int)(vec->wallX * (double)info->texture.texwidth);
		if (vec->side == 0 && vec->rayDirX > 0)
			texX = info->texture.texwidth - texX - 1;
		if (vec->side == 1 && vec->rayDirY < 0)
			texX = info->texture.texwidth - texX - 1;
		double step = 1.0 * info->texture.texheight / vec->lineHeight;
		double texPos = (vec->drawStart - info->height / 2 + vec->lineHeight / 2) * step;
		y = vec->drawStart;
		while (y < vec->drawEnd)
		{
			int texY = (int)texPos & (info->texture.texheight - 1);
			texPos += step;
			int color = info->texture.texture[texNum][info->texture.texheight * texY + texX];
			if (vec->side == 1)
				color = (color >> 1) & 8355711;
			info->texture.buf[y][x] = color;
			y++;
		}
		info->zBuffer[x] = vec->perpWallDist;
		x++;
	}
}

void draw_sprite(t_info *info)
{
	int i;
	int y;
	int stripe;

	i = 0;
	while (i < numSprites)
	{
		info->spriteOrder[i] = i;
		info->spriteDistance[i] = ((info->posX - info->sprite[i].x) * (info->posX - info->sprite[i].x) + (info->posY - info->sprite[i].y) * (info->posY - info->sprite[i].y));
		i++;
	}
	sortSprites(info->spriteOrder, info->spriteDistance, numSprites);
	i = 0;
	while (i < numSprites)
	{
		double spriteX = info->sprite[info->spriteOrder[i]].x - info->posX;
		double spriteY = info->sprite[info->spriteOrder[i]].y - info->posY;
		double invDet = 1.0 / (info->planeX * info->dirY - info->dirX * info->planeY);
		double transformX = invDet * (info->dirY * spriteX - info->dirX * spriteY);
		double transformY = invDet * (-info->planeY * spriteX + info->planeX * spriteY);
		int spriteScreenX = (int)((info->width / 2) * (1 + transformX / transformY));
		int vMoveScreen = (int)(vMove / transformY);
		int spriteHeight = (int)fabs((info->height / transformY) / vDiv);
		int drawStartY = -spriteHeight / 2 + info->height / 2 + vMoveScreen;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + info->height / 2 + vMoveScreen;
		if (drawEndY >= info->height)
			drawEndY = info->height - 1;
		int spriteWidth = (int)fabs((info->height / transformY) / uDiv);
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= info->width)
			drawEndX = info->width - 1;
		stripe = drawStartX;
		while (stripe < drawEndX)
		{
			y = drawStartY;
			int texX = (int)((256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * info->texture.texwidth / spriteWidth) / 256);
			if (transformY > 0 && stripe > 0 && stripe < info->width && transformY < info->zBuffer[stripe])
				while (y < drawEndY)
				{
					int d = (y - vMoveScreen) * 256 - info->height * 128 + spriteHeight * 128;
					int texY = ((d * info->texture.texheight) / spriteHeight) / 256;
					int color = info->texture.texture[info->sprite[info->spriteOrder[i]].texture][info->texture.texwidth * texY + texX]; //get current color from the texture
					if ((color & 0x00FFFFFF) != 0)
						info->texture.buf[y][stripe] = color;
					y++;
				}
			stripe++;
		}
		i++;
	}
}

void calc(t_info *info)
{
	t_vec vec;

	draw_floor(info);
	draw_wall(info, &vec);
	draw_sprite(info);
}