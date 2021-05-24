/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 13:53:33 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/24 16:44:13 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		rearrange_all(t_info *info)
{
	apply_player_orientation(info);
	info->mlx = mlx_init();
	info->win = mlx_new_window(info->mlx, info->width, info->height, "Cub3d");
	allocate_buffer(info);
	load_texture(info);
	set_sprite(info);
	return (1);
}

void	apply_player_orientation(t_info *info)
{
	double degree;

	degree = 0;
	if (info->player.dir == 'N')
		degree = 0;
	else if (info->player.dir == 'S')
		degree = 180;
	else if (info->player.dir == 'E')
		degree = 270;
	else if (info->player.dir == 'W')
		degree = 90;
	rotate_player(&info->player, degree * (PI / 180));
}

void	allocate_buffer(t_info *info)
{
	int i;

	if (!(info->buf = ft_calloc(info->height, sizeof(int **))))
		ft_strexit("ERROR: Malloc Fail!");
	i = 0;
	while (i < info->height)
	{
		if (!(info->buf[i] = ft_calloc(info->width, sizeof(int *))))
			ft_strexit("ERROR: Malloc Fail!");
		i++;
	}
	if (!(info->zBuffer = ft_calloc(info->width, sizeof(double *))))
		ft_strexit("ERROR: Malloc Fail!");
}

void	load_texture(t_info *info)
{
	t_img	img;

	load_image(info, info->texture.texture[WEST], info->texture.path[WEST], &img);
	free(info->texture.path[WEST]);
	load_image(info, info->texture.texture[EAST], info->texture.path[EAST], &img);
	free(info->texture.path[EAST]);
	load_image(info, info->texture.texture[SOUTH], info->texture.path[SOUTH], &img);
	free(info->texture.path[SOUTH]);
	load_image(info, info->texture.texture[NORTH], info->texture.path[NORTH], &img);
	free(info->texture.path[NORTH]);
	load_image(info, info->texture.texture[SPR], info->texture.path[SPR], &img);
	free(info->texture.path[SPR]);
}

void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	int		x;
	int		y;

	img->img = mlx_xpm_file_to_image(info->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(
						img->img, &img->bpp, &img->size_l, &img->endian);
	y = 0;
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			texture[img->img_width * y + x] =
							img->data[img->img_width * y + (img->img_width - x - 1)];
			x++;
		}
		y++;
	}
	mlx_destroy_image(info->mlx, img->img);
}

void set_sprite(t_info *info)
{
	int x;
	int y;
	int i;

	if (!(info->sprite = (t_sprite *)malloc(sizeof(t_sprite) * info->num_sprite)))
		ft_strexit("ERROR: Malloc Fail!");
	if (!(info->spriteOrder = (int *)malloc(sizeof(int) * info->num_sprite)))
		ft_strexit("ERROR: Malloc Fail!");
	if (!(info->spriteDistance = (double *)malloc(sizeof(double) * info->num_sprite)))
		ft_strexit("ERROR: Malloc Fail!");
	i = 0;
	y = 0;
	while (y < info->map.mapwidth)
	{
		x = 0;
		while (x < info->map.mapheight)
		{
			if (info->map.map[y][x] == '2')
			{
				info->sprite[i].x = y + 0.5;
				info->sprite[i++].y = x + 0.5;
			}
			if (i == info->num_sprite)
				break;
			x++;
		}
		y++;
	}
}

void	rotate_player(t_player *player, double degree)
{
	double oldDirX = player->dirX;
	double oldPlaneX = player->planeX;
		
	player->dirX = player->dirX * cos(degree) - player->dirY * sin(degree);
	player->dirY = oldDirX * sin(degree) + player->dirY * cos(degree);
	player->planeX = player->planeX * cos(degree) - player->planeY * sin(degree);
	player->planeY = oldPlaneX * sin(degree) + player->planeY * cos(degree);
}