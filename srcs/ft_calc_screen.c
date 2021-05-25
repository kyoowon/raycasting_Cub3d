/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 13:51:12 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/26 01:37:10 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	draw_floor_ceiling(t_info *info)
{
	int		x;
	int		y;
	int		color;

	y = info->height / 2 + 1;
	while (y < info->height)
	{
		x = 0;
		while (++x < info->width)
		{
			color = info->texture.floor;
			info->buf[y][x] = color;
			color = info->texture.ceiling;
			info->buf[info->height - y - 1][x] = color;
		}
		y++;
	}
}

void	sort_order(t_pair *orders, int amount)
{
	t_pair	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < amount)
	{
		j = 0;
		while (j < amount - 1)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
			j++;
		}
		i++;
	}
}

void	sort_sprites(int *order, double *dist, int amount)
{
	t_pair	*sprites;
	int		i;

	sprites = (t_pair *)malloc(sizeof(t_pair) * amount);
	i = 0;
	while (i < amount)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
		i++;
	}
	sort_order(sprites, amount);
	i = 0;
	while (i < amount)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
		i++;
	}
	free(sprites);
}

void	calc_screen(t_info *info)
{
	int		i;
	t_vec	vec;
	t_svec	svec;

	draw_floor_ceiling(info);
	draw_wall(info, &vec);
	i = 0;
	while (i < info->num_sprite)
	{
		info->s_order[i] = i;
		info->s_distance[i] = ((info->player.pos_x - info->sprite[i].x) *
								(info->player.pos_x - info->sprite[i].x) +
								(info->player.pos_y - info->sprite[i].y) *
								(info->player.pos_y - info->sprite[i].y));
		i++;
	}
	sort_sprites(info->s_order, info->s_distance, info->num_sprite);
	draw_sprite(info, &svec);
}
