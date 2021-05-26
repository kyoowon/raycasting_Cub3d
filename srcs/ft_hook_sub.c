/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook_sub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyulee <kyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 06:24:42 by kyulee            #+#    #+#             */
/*   Updated: 2021/05/27 07:33:02 by kyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	press_key_w(t_player *player, t_map map)
{
	if (map.map[(int)(player->pos_x + player->dir_x * player->m_speed)]
				[(int)(player->pos_y)] != '1')
		player->pos_x += player->dir_x * player->m_speed;
	if (map.map[(int)(player->pos_x)]
				[(int)(player->pos_y + player->dir_y * player->m_speed)] != '1')
		player->pos_y += player->dir_y * player->m_speed;
}

void	press_key_s(t_player *player, t_map map)
{
	if (map.map[(int)(player->pos_x - player->dir_x * player->m_speed)]
				[(int)(player->pos_y)] != '1')
		player->pos_x -= player->dir_x * player->m_speed;
	if (map.map[(int)(player->pos_x)]
				[(int)(player->pos_y - player->dir_y * player->m_speed)] != '1')
		player->pos_y -= player->dir_y * player->m_speed;
}

void	press_key_d(t_player *player, t_map map)
{
	if (map.map[(int)(player->pos_x + player->dir_y * player->m_speed)]
			[(int)(player->pos_y)] != '1')
		player->pos_x += player->dir_y * player->m_speed;
	if (map.map[(int)(player->pos_x)]
				[(int)(player->pos_y - player->dir_x * player->m_speed)] != '1')
		player->pos_y -= player->dir_x * player->m_speed;
}

void	press_key_a(t_player *player, t_map map)
{
	if (map.map[(int)(player->pos_x - player->dir_y * player->m_speed)]
		[(int)(player->pos_y)] != '1')
		player->pos_x -= player->dir_y * player->m_speed;
	if (map.map[(int)(player->pos_x)]
			[(int)(player->pos_y + player->dir_x * player->m_speed)] != '1')
		player->pos_y += player->dir_x * player->m_speed;
}
