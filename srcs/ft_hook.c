/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyulee <kyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 13:54:56 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/27 07:33:06 by kyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_update(t_info *info)
{
	if (info->key.key_w)
		press_key_w(&info->player, info->map);
	if (info->key.key_s)
		press_key_s(&info->player, info->map);
	if (info->key.key_d)
		press_key_d(&info->player, info->map);
	if (info->key.key_a)
		press_key_a(&info->player, info->map);
	if (info->key.key_ar_r)
		rotate_player(&info->player, -info->player.r_speed);
	if (info->key.key_ar_l)
		rotate_player(&info->player, info->player.r_speed);
	if (info->key.key_esc)
		event_exit(info);
}

int		key_press(int key, t_info *info)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W)
		info->key.key_w = 1;
	else if (key == K_A)
		info->key.key_a = 1;
	else if (key == K_S)
		info->key.key_s = 1;
	else if (key == K_D)
		info->key.key_d = 1;
	else if (key == K_AR_L)
		info->key.key_ar_l = 1;
	else if (key == K_AR_R)
		info->key.key_ar_r = 1;
	return (0);
}

int		key_release(int key, t_info *info)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W)
		info->key.key_w = 0;
	else if (key == K_A)
		info->key.key_a = 0;
	else if (key == K_S)
		info->key.key_s = 0;
	else if (key == K_D)
		info->key.key_d = 0;
	else if (key == K_AR_L)
		info->key.key_ar_l = 0;
	else if (key == K_AR_R)
		info->key.key_ar_r = 0;
	return (0);
}

void	rotate_player(t_player *p, double degree)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = p->dir_x;
	oldplane_x = p->plane_x;
	p->dir_x = p->dir_x * cos(degree) - p->dir_y * sin(degree);
	p->dir_y = olddir_x * sin(degree) + p->dir_y * cos(degree);
	p->plane_x = p->plane_x * cos(degree) - p->plane_y * sin(degree);
	p->plane_y = oldplane_x * sin(degree) + p->plane_y * cos(degree);
}

int		event_exit(t_info *info)
{
	ft_frees_nbr(info->buf);
	ft_frees(info->map.map);
	free(info->sprite);
	free(info->s_order);
	free(info->s_distance);
	free(info->zbuffer);
	mlx_destroy_image(info->mlx, info->img.img);
	mlx_destroy_window(info->mlx, info->win);
	exit(0);
}
