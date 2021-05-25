/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 13:54:56 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/26 01:42:46 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	key_update(t_player *player, t_map map, t_key key)
{
	if (key.key_w)
	{
		if (map.map[(int)(player->pos_x + player->dir_x * player->m_speed)]
				[(int)(player->pos_y)] != '1')
			player->pos_x += player->dir_x * player->m_speed;
		if (map.map[(int)(player->pos_x)]
				[(int)(player->pos_y + player->dir_y * player->m_speed)] != '1')
			player->pos_y += player->dir_y * player->m_speed;
	}
	if (key.key_s)
	{
		if (map.map[(int)(player->pos_x - player->dir_x * player->m_speed)]
				[(int)(player->pos_y)] != '1')
			player->pos_x -= player->dir_x * player->m_speed;
		if (map.map[(int)(player->pos_x)]
				[(int)(player->pos_y - player->dir_y * player->m_speed)] != '1')
			player->pos_y -= player->dir_y * player->m_speed;
	}
	if (key.key_d || key.key_ar_r)
		rotate_player(player, -player->r_speed);
	if (key.key_a || key.key_ar_l)
		rotate_player(player, player->r_speed);
	if (key.key_esc)
		exit(0);
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
