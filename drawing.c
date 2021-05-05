/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 13:53:33 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/05 15:20:24 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

void	verLine(t_info *info, int x, int winy1, int winy2, int mapY, int mapX, int side)
{
	int	y;

	int	color;

	if (info->map[mapY][mapX] == 1)
		color = 0xFF0000;
	else if (info->map[mapY][mapX] == 2)
		color = 0x00FF00;
	else if (info->map[mapY][mapX] == 3)
		color = 0x0000FF;
	else if (info->map[mapY][mapX] == 4)
		color = 0xFFFFFF;
	else
		color = 0xFFFF00;
	if (side == 1)
		color = color / 2;
	y = winy1;
	while (y <= winy2)
	{
		mlx_pixel_put(info->mlx, info->win, x, y, color);
		y++;
	}
}

void	draw(t_info *info)
{
	for (int y = 0; y < info->height; y++)
	{
		for (int x = 0; x < info->width; x++)
		{
			info->img.data[y * info->width + x] = info->buf[y][x];
		}
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

int init_texture(t_info *info)
{
	info->buf = (int **)malloc(sizeof(int *) * info->height);
	for (int i = 0; i < info->height; i++)
	{
		info->buf[i] = (int *)malloc(sizeof(int) * info->width);
	}

	for (int i = 0; i < info->height; i++)
	{
		for (int j = 0; j < info->width; j++)
		{
			info->buf[i][j] = 0;
		}
	}
	if (!(info->texture = (int **)malloc(sizeof(int *) * 8)))
		return (-1);
	for (int i = 0; i < 8; i++)
	{
		if (!(info->texture[i] = (int *)malloc(sizeof(int) * (info->texheight * info->texwidth))))
			return (-1);
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < info->texheight * info->texwidth; j++)
		{
			info->texture[i][j] = 0;
		}
	}
	return (0);
}

void	draw_texture(t_info *info)
{
	for (int x = 0; x < info->texwidth; x++)
	{
		for (int y = 0; y < info->texheight; y++)
		{
			int xorcolor = (x * 256 / info->texwidth) ^ (y * 256 / info->texheight);
			int ycolor = y * 256 / info->texheight;
			int xycolor = y * 128 / info->texheight + x * 128 / info->texwidth;
			info->texture[0][info->texwidth * y + x] = 65536 * 254 * (x != y && x != info->texwidth - y); //flat red texture with black cross
			info->texture[1][info->texwidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			info->texture[2][info->texwidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			info->texture[3][info->texwidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			info->texture[4][info->texwidth * y + x] = 256 * xorcolor; //xor green
			info->texture[5][info->texwidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
			info->texture[6][info->texwidth * y + x] = 65536 * ycolor; //red gradient
			info->texture[7][info->texwidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
		}
	}
}
void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(info->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	for (int y = 0; y < img->img_height; y++)
	{
		for (int x = 0; x < img->img_width; x++)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}
	mlx_destroy_image(info->mlx, img->img);
}

void	load_texture(t_info *info)
{
	t_img	img;

	load_image(info, info->texture[0], "textures/eagle.xpm", &img);
	load_image(info, info->texture[1], "textures/redbrick.xpm", &img);
	load_image(info, info->texture[2], "textures/purplestone.xpm", &img);
	load_image(info, info->texture[3], "textures/greystone.xpm", &img);
	load_image(info, info->texture[4], "textures/bluestone.xpm", &img);
	load_image(info, info->texture[5], "textures/mossy.xpm", &img);
	load_image(info, info->texture[6], "textures/wood.xpm", &img);
	load_image(info, info->texture[7], "textures/colorstone.xpm", &img);
}