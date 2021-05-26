/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyulee <kyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 20:02:39 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/27 07:33:33 by kyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_dda(t_player *player, t_vec *vec)
{
	if (vec->rdir_x < 0)
	{
		vec->step_x = -1;
		vec->sdist_x = (player->pos_x - vec->map_x) * vec->ddist_x;
	}
	else
	{
		vec->step_x = 1;
		vec->sdist_x = (vec->map_x + 1.0 - player->pos_x) * vec->ddist_x;
	}
	if (vec->rdir_y < 0)
	{
		vec->step_y = -1;
		vec->sdist_y = (player->pos_y - vec->map_y) * vec->ddist_y;
	}
	else
	{
		vec->step_y = 1;
		vec->sdist_y = (vec->map_y + 1.0 - player->pos_y) * vec->ddist_y;
	}
}

void	calc_dda_hit(t_info *info, t_vec *vec, int *wall_type)
{
	while (vec->hit == 0)
	{
		if (vec->sdist_x < vec->sdist_y)
		{
			if (vec->step_x == 1)
				*wall_type = 1;
			else
				*wall_type = 0;
			vec->sdist_x += vec->ddist_x;
			vec->map_x += vec->step_x;
			vec->side = 0;
		}
		else
		{
			if (vec->step_y == 1)
				*wall_type = 2;
			else
				*wall_type = 3;
			vec->sdist_y += vec->ddist_y;
			vec->map_y += vec->step_y;
			vec->side = 1;
		}
		if (info->map.map[vec->map_x][vec->map_y] == '1')
			vec->hit = 1;
	}
}

void	calc_perpwalldist(t_player *p, t_vec *v, int height)
{
	if (v->side == 0)
		v->pwdist = (v->map_x - p->pos_x + (1 - v->step_x) / 2) / v->rdir_x;
	else
		v->pwdist = (v->map_y - p->pos_y + (1 - v->step_y) / 2) / v->rdir_y;
	v->lineheight = (int)(height / v->pwdist);
	v->drawstart = -v->lineheight / 2 + height / 2;
	if (v->drawstart < 0)
		v->drawstart = 0;
	v->drawend = v->lineheight / 2 + height / 2;
	if (v->drawend >= height)
		v->drawend = height - 1;
	if (v->side == 0)
		v->wall_x = p->pos_y + v->pwdist * v->rdir_y;
	else
		v->wall_x = p->pos_x + v->pwdist * v->rdir_x;
	v->wall_x -= floor((v->wall_x));
}

void	calc_texture_wall(t_info *info, t_vec *vec, int x, int wall_type)
{
	int		y;
	int		color;
	double	step;
	double	texpos;

	vec->tex_x = (int)(vec->wall_x * (double)TEXWIDTH);
	if (vec->side == 0 && vec->rdir_x < 0)
		vec->tex_x = TEXWIDTH - vec->tex_x - 1;
	if (vec->side == 1 && vec->rdir_y > 0)
		vec->tex_x = TEXWIDTH - vec->tex_x - 1;
	step = 1.0 * TEXHEIGHT / vec->lineheight;
	texpos = (vec->drawstart - info->height / 2 + vec->lineheight / 2) * step;
	y = vec->drawstart;
	while (y < vec->drawend)
	{
		vec->tex_y = (int)texpos & (TEXHEIGHT - 1);
		texpos += step;
		color = info->texture.texture[wall_type]
							[TEXHEIGHT * vec->tex_y + vec->tex_x];
		info->buf[y][x] = color;
		y++;
	}
	info->zbuffer[x] = vec->pwdist;
}

void	draw_wall(t_info *info, t_vec *vec)
{
	int		x;
	int		wall_type;

	x = 0;
	while (x < info->width)
	{
		vec->camera = 2 * x / (double)info->width - 1;
		vec->rdir_x = info->player.dir_x + info->player.plane_x * vec->camera;
		vec->rdir_y = info->player.dir_y + info->player.plane_y * vec->camera;
		vec->map_x = (int)info->player.pos_x;
		vec->map_y = (int)info->player.pos_y;
		vec->ddist_x = fabs(1 / vec->rdir_x);
		vec->ddist_y = fabs(1 / vec->rdir_y);
		vec->hit = 0;
		init_dda(&info->player, vec);
		calc_dda_hit(info, vec, &wall_type);
		calc_perpwalldist(&info->player, vec, info->height);
		calc_texture_wall(info, vec, x, wall_type);
		x++;
	}
}
