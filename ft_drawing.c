/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 13:53:33 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/11 17:39:15 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

void	verLine(t_info *info, int x, int winy1, int winy2, int mapY, int mapX, int side)
{
	int	y;
	int	color;

	if (info->map.map[mapY][mapX] == 1)
		color = 0xFF0000;
	else if (info->map.map[mapY][mapX] == 2)
		color = 0x00FF00;
	else if (info->map.map[mapY][mapX] == 3)
		color = 0x0000FF;
	else if (info->map.map[mapY][mapX] == 4)
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
	int x;
	int y;

	y = 0;
	while (y < info->height)
	{
		x = 0;
		while (x < info->width)
		{
			info->img.data[y * info->width + x] = info->texture.buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

int init_texture(t_info *info)
{
	int i;
	int j;
	if (!(info->texture.buf = (int **)malloc(sizeof(int *) * info->height)))
		return (-1);
	i = 0;
	while (i < info->height)
	{
		if (!(info->texture.buf[i] = (int *)malloc(sizeof(int) * info->width)))
			return (-1);
		i++;
	}
	i = 0;
	while (i < info->height)
	{
		j = 0;
		while (j < info->width)
		{
			info->texture.buf[i][j] = 0;
			j++;
		}
		i++;
	}
	if (!(info->texture.texture = (int **)malloc(sizeof(int *) * 11)))
		return (-1);
	i = 0;
	while (i < 11)
	{
		if (!(info->texture.texture[i] = (int *)malloc(sizeof(int) * (info->texture.texheight * info->texture.texwidth))))
			return (-1);
		i++;
	}
	i = 0;
	while (i < 11)
	{
		j = 0;
		while (j < info->texture.texheight * info->texture.texwidth)
		{
			info->texture.texture[i][j] = 0;
			j++;
		}
		i++;
	}
	if (!(info->zBuffer = (double *)malloc(sizeof(double)* info->width)))
		return (-1);
	return (0);
}

void	draw_texture(t_info *info)
{
	int x;
	int y;

	x = 0;
	while (x < info->texture.texwidth)
	{
		y = 0;
		while (y < info->texture.texheight)
		{
			int xorcolor = (x * 256 / info->texture.texwidth) ^ (y * 256 / info->texture.texheight);
			int ycolor = y * 256 / info->texture.texheight;
			int xycolor = y * 128 / info->texture.texheight + x * 128 / info->texture.texwidth;
			info->texture.texture[0][info->texture.texwidth * y + x] = 65536 * 254 * (x != y && x != info->texture.texwidth - y);
			info->texture.texture[1][info->texture.texwidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;
			info->texture.texture[2][info->texture.texwidth * y + x] = 256 * xycolor + 65536 * xycolor;
			info->texture.texture[3][info->texture.texwidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
			info->texture.texture[4][info->texture.texwidth * y + x] = 256 * xorcolor;
			info->texture.texture[5][info->texture.texwidth * y + x] = 65536 * 192 * (x % 16 && y % 16);
			info->texture.texture[6][info->texture.texwidth * y + x] = 65536 * ycolor;
			info->texture.texture[7][info->texture.texwidth * y + x] = 128 + 256 * 128 + 65536 * 128;
			y++;
		}
		x++;
	}
}

void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	int x;
	int y;
	img->img = mlx_xpm_file_to_image(info->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	y = 0;
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(info->mlx, img->img);
}

void	load_texture(t_info *info)
{
	t_img	img;

	load_image(info, info->texture.texture[0], "textures/eagle.xpm", &img);
	load_image(info, info->texture.texture[1], "textures/redbrick.xpm", &img);
	load_image(info, info->texture.texture[2], "textures/purplestone.xpm", &img);
	load_image(info, info->texture.texture[3], "textures/greystone.xpm", &img);
	load_image(info, info->texture.texture[4], "textures/bluestone.xpm", &img);
	load_image(info, info->texture.texture[5], "textures/mossy.xpm", &img);
	load_image(info, info->texture.texture[6], "textures/wood.xpm", &img);
	load_image(info, info->texture.texture[7], "textures/colorstone.xpm", &img);
	load_image(info, info->texture.texture[8], "textures/barrel.xpm", &img);
	load_image(info, info->texture.texture[9], "textures/pillar.xpm", &img);
	load_image(info, info->texture.texture[10], "textures/greenlight.xpm", &img);
}