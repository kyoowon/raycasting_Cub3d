/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 16:06:30 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/27 00:02:04 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		main_loop(t_info *info)
{
	calc_screen(info);
	draw_window(info);
	key_update(&info->player, info->map, info->key, info);
	return (0);
}

void	draw_window(t_info *info)
{
	int y;
	int x;

	y = 0;
	while (y < info->height)
	{
		x = 0;
		while (x < info->width)
		{
			info->img.data[y * info->width + x] = info->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

void	draw_bitmap(t_info *info)
{
	int y;
	int x;

	calc_screen(info);
	y = 0;
	while (y < info->height)
	{
		x = 0;
		while (x < info->width)
		{
			info->img.data[y * info->width + x] = info->buf[y][x];
			x++;
		}
		y++;
	}
	save_bitmap(info);
}

void	init_info(t_info *info)
{
	info->mlx = mlx_init();
	info->width = 0;
	info->height = 0;
	ft_memset(info->texture.path, 0, 6);
	info->texture.floor = -1;
	info->texture.ceiling = -1;
	info->map.map = NULL;
	info->map.mwidth = 0;
	info->map.mheight = 0;
	info->player.dir = '\0';
	info->sprite = NULL;
	info->num_sprite = 0;
	info->buf = NULL;
	info->zbuffer = NULL;
	info->key.key_a = 0;
	info->key.key_w = 0;
	info->key.key_d = 0;
	info->key.key_s = 0;
	info->key.key_esc = 0;
	info->key.key_ar_r = 0;
	info->key.key_ar_l = 0;
}

int		main(int argc, char *argv[])
{
	t_info	info;
	int		save;

	save = validate_arguments(argc, argv[2]);
	init_info(&info);
	open_cubfile(argv[1], &info);
	validate_info(&info);
	read_map(&info, info.line);
	validate_map(&info);
	setting_all(&info);
	if (save == OFF)
	{
		info.win = mlx_new_window(info.mlx, info.width, info.height, "Cub3d");
		mlx_loop_hook(info.mlx, &main_loop, &info);
		mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
		mlx_hook(info.win, X_EVENT_KEY_RELEASE, 0, &key_release, &info);
		mlx_hook(info.win, DESTROY_NOTIFY, 1L << 17, &event_exit, &info);
		mlx_loop(info.mlx);
	}
	else if (save == ON)
		draw_bitmap(&info);
	return (0);
}
