/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 13:53:33 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/26 21:08:46 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	setting_all(t_info *info)
{
	apply_player_orientation(&info->player);
	allocate_buffer(info);
	load_texture(info);
	set_malloc_sprite(info);
	info->img.img = mlx_new_image(info->mlx, info->width, info->height);
	info->img.data = (int *)mlx_get_data_addr(info->img.img,
					&info->img.bpp, &info->img.size_l, &info->img.endian);
}

void	apply_player_orientation(t_player *player)
{
	double olddir_x;
	double oldplane_x;
	double degree;

	olddir_x = player->dir_x;
	oldplane_x = player->plane_x;
	degree = 0;
	if (player->dir == 'N')
		degree = 0;
	else if (player->dir == 'S')
		degree = 180;
	else if (player->dir == 'E')
		degree = 270;
	else if (player->dir == 'W')
		degree = 90;
	rotate_player(player, degree * PI / 180);
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
	if (!(info->zbuffer = ft_calloc(info->width, sizeof(double *))))
		ft_strexit("ERROR: Malloc Fail!");
}

void	load_texture(t_info *info)
{
	t_img	img;

	load_image(info, info->texture.texture[WEST],
									info->texture.path[WEST], &img);
	free(info->texture.path[WEST]);
	load_image(info, info->texture.texture[EAST],
									info->texture.path[EAST], &img);
	free(info->texture.path[EAST]);
	load_image(info, info->texture.texture[SOUTH],
									info->texture.path[SOUTH], &img);
	free(info->texture.path[SOUTH]);
	load_image(info, info->texture.texture[NORTH],
									info->texture.path[NORTH], &img);
	free(info->texture.path[NORTH]);
	load_image(info, info->texture.texture[SPR],
									info->texture.path[SPR], &img);
	free(info->texture.path[SPR]);
}

void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	int		x;
	int		y;

	img->img = mlx_xpm_file_to_image(info->mlx, path,
						&img->img_width, &img->img_height);
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
