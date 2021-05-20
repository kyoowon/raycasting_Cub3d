/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 13:53:33 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/20 18:04:27 by kyuwonlee        ###   ########.fr       */
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
	// set_sprite(info);
	info->img.img = mlx_new_image(info->mlx, info->width, info->height);
	info->img.data = (int *)mlx_get_data_addr(info->img.img,
			&info->img.bpp, &info->img.size_l, &info->img.endian);
	return (1);
}

void	apply_player_orientation(t_info *info)
{
	int degree;

	degree = 0;
	if (info->player.dir == 'N')
		degree = 90;
	else if (info->player.dir == 'S')
		degree = 270;
	else if (info->player.dir == 'E')
		degree = 0;
	else if (info->player.dir == 'W')
		degree = 180;
	// rotate_player(&info->player, degree * (PI / 180));
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