/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 13:51:12 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/05 15:19:52 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

void	calc(t_info *info)
{
	int		x;
	t_vec	vec;

	x = 0;
	while (x < info->width)
	{
		vec.cameraX = 2 * x / (double)info->width - 1;
		vec.rayDirX = info->dirX + info->planeX * vec.cameraX;
		vec.rayDirY = info->dirY + info->planeY * vec.cameraX;
		vec.deltaDistX = fabs(1 / vec.rayDirX);
		vec.deltaDistY = fabs(1 / vec.rayDirY);
		vec.mapX = (int)info->posX;
		vec.mapY = (int)info->posY;
		vec.hit = 0;

		if (vec.rayDirX < 0)
		{
			vec.stepX = -1;
			vec.sideDistX = (info->posX - vec.mapX) * vec.deltaDistX;
		}
		else
		{
			vec.stepX = 1;
			vec.sideDistX = (vec.mapX + 1.0 - info->posX) * vec.deltaDistX;
		}
		if (vec.rayDirY < 0)
		{
			vec.stepY = -1;
			vec.sideDistY = (info->posY - vec.mapY) * vec.deltaDistY;
		}
		else
		{
			vec.stepY = 1;
			vec.sideDistY = (vec.mapY + 1.0 - info->posY) * vec.deltaDistY;
		}
		while (vec.hit == 0)
		{
			if (vec.sideDistX < vec.sideDistY)
			{
				vec.sideDistX += vec.deltaDistX;
				vec.mapX += vec.stepX;
				vec.side = 0;
			}
			else
			{
				vec.sideDistY += vec.deltaDistY;
				vec.mapY += vec.stepY;
				vec.side = 1;
			}
			if (info->map[vec.mapX][vec.mapY] > 0)
				vec.hit = 1;
		}

		if (vec.side == 0)
			vec.perpWallDist = (vec.mapX - info->posX + (1 - vec.stepX) / 2) / vec.rayDirX;
		else
			vec.perpWallDist = (vec.mapY - info->posY + (1 - vec.stepY) / 2) / vec.rayDirY;

		int lineHeight = (int)(info->height / vec.perpWallDist);
		int drawStart = -lineHeight / 2 + info->height / 2;

		if(drawStart < 0)
			drawStart = 0;

		int drawEnd = lineHeight / 2 + info->height / 2;

		if(drawEnd >= info->height)
			drawEnd = info->height - 1;

		// verLine(info, x, drawStart, drawEnd, mapY, mapX, side);

		int texNum = info->map[vec.mapX][vec.mapY] - 1;
		
		if (vec.side == 0)
			vec.wallX = info->posY + vec.perpWallDist * vec.rayDirY;
		else
			vec.wallX = info->posX + vec.perpWallDist * vec.rayDirX;
		vec.wallX -= floor(vec.wallX);

		int texX = (int)(vec.wallX * (double)TEXWIDTH);
		if (vec.side == 0 && vec.rayDirX > 0)
			texX = TEXWIDTH - texX - 1;
		if (vec.side == 1 && vec.rayDirY < 0)
			texX = TEXWIDTH - texX - 1;

		double step = 1.0 * TEXHEIGHT / lineHeight;
		double texPos = (drawStart - info->height / 2 + lineHeight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++)
		{
			int texY = (int)texPos & (TEXHEIGHT - 1);
			texPos += step;
			int color = info->texture[texNum][TEXHEIGHT * texY + texX];
			if (vec.side == 1)
				color = (color >> 1) & 8355711;
			info->buf[y][x] = color;
		}

		//FLOOR CASTING (vertical version, directly after drawing the vertical wall stripe for the current x)
		double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall
		//4 different wall directions possible
		if(vec.side == 0 && vec.rayDirX > 0)
		{
			floorXWall = vec.mapX;
			floorYWall = vec.mapY + vec.wallX;
		}
		else if(vec.side == 0 && vec.rayDirX < 0)
		{
			floorXWall = vec.mapX + 1.0;
			floorYWall = vec.mapY + vec.wallX;
		}
		else if(vec.side == 1 && vec.rayDirY > 0)
		{
			floorXWall = vec.mapX + vec.wallX;
			floorYWall = vec.mapY;
		}
		else
		{
			floorXWall = vec.mapX + vec.wallX;
			floorYWall = vec.mapY + 1.0;
		}

		double distWall, distPlayer, currentDist;

		distWall = vec.perpWallDist;
		distPlayer = 0.0;

		if (drawEnd < 0) drawEnd = info->height; //becomes < 0 when the integer overflows

		//draw the floor from drawEnd to the bottom of the screen
		for(int y = drawEnd + 1; y < info->height; y++)
		{
			currentDist = info->height / (2.0 * y - info->height); //you could make a small lookup table for this instead

			double weight = (currentDist - distPlayer) / (distWall - distPlayer);

			double currentFloorX = weight * floorXWall + (1.0 - weight) * info->posX;
			double currentFloorY = weight * floorYWall + (1.0 - weight) * info->posY;

			int floorTexX, floorTexY;
			floorTexX = (int)(currentFloorX * info->texwidth) % info->texwidth;
			floorTexY = (int)(currentFloorY * info->texheight) % info->texheight;

			int checkerBoardPattern = ((int)(currentFloorX) + (int)(currentFloorY)) % 2;
			int floorTexture;
			if(checkerBoardPattern == 0) floorTexture = 3;
			else floorTexture = 4;

			//floor
			info->buf[y][x] = (info->texture[floorTexture][info->texwidth * floorTexY + floorTexX] >> 1) & 8355711;
			//ceiling (symmetrical!)
			info->buf[info->height - y][x] = info->texture[6][info->texwidth * floorTexY + floorTexX];
		}
		x++;
	}
}