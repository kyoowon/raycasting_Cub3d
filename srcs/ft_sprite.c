/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyulee <kyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 19:05:20 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/27 07:33:25 by kyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_malloc_sprite(t_info *info)
{
	if (!(info->sprite =
				(t_sprite *)malloc(sizeof(t_sprite) * info->num_sprite)))
		ft_strexit("ERROR: Malloc Fail!");
	if (!(info->s_order = (int *)malloc(sizeof(int) * info->num_sprite)))
		ft_strexit("ERROR: Malloc Fail!");
	if (!(info->s_distance =
					(double *)malloc(sizeof(double) * info->num_sprite)))
		ft_strexit("ERROR: Malloc Fail!");
	set_sprite(info);
}

void	set_sprite(t_info *info)
{
	int		x;
	int		y;
	int		i;

	i = 0;
	y = 0;
	while (y < info->map.mwidth)
	{
		x = 0;
		while (x < info->map.mheight)
		{
			if (info->map.map[y][x] == SPRITE)
			{
				info->sprite[i].x = y + 0.5;
				info->sprite[i++].y = x + 0.5;
			}
			if (i == info->num_sprite)
				break ;
			x++;
		}
		y++;
	}
}

void	scaling_sprites(t_info *info, t_svec *svec)
{
	svec->vmove_s = (int)(VMOVE / svec->trans_y);
	svec->height = (int)fabs((info->height / svec->trans_y) / VDIV);
	svec->drawstart_y = -svec->height / 2 + info->height / 2 + svec->vmove_s;
	if (svec->drawstart_y < 0)
		svec->drawstart_y = 0;
	svec->drawend_y = svec->height / 2 + info->height / 2 + svec->vmove_s;
	if (svec->drawend_y >= info->height)
		svec->drawend_y = info->height - 1;
	svec->width = (int)fabs((info->height / svec->trans_y) / UDIV);
	svec->drawstart_x = -svec->width / 2 + svec->screen;
	if (svec->drawstart_x < 0)
		svec->drawstart_x = 0;
	svec->drawend_x = svec->width / 2 + svec->screen;
	if (svec->drawend_x >= info->width)
		svec->drawend_x = info->width - 1;
}

void	drawing_sprite(t_info *info, t_svec *svec)
{
	int		y;
	int		d;

	svec->stripe = svec->drawstart_x;
	while (svec->stripe < svec->drawend_x)
	{
		y = svec->drawstart_y;
		svec->tex_x = (int)((256 * (svec->stripe - (-svec->width
			/ 2 + svec->screen)) * TEXWIDTH / svec->width) / 256);
		if (svec->trans_y > 0 && svec->stripe > 0 && svec->stripe
				< info->width && svec->trans_y < info->zbuffer[svec->stripe])
			while (y < svec->drawend_y)
			{
				d = (y - svec->vmove_s) * 256 -
								info->height * 128 + svec->height * 128;
				svec->tex_y = ((d * TEXHEIGHT) / svec->height) / 256;
				svec->color = info->texture.texture[SPR]
								[TEXWIDTH * svec->tex_y + svec->tex_x];
				if ((svec->color & 0x00FFFFFF) != 0)
					info->buf[y][svec->stripe] = svec->color;
				y++;
			}
		svec->stripe++;
	}
}

void	draw_sprite(t_info *info, t_svec *svec)
{
	int		i;

	i = 0;
	while (i < info->num_sprite)
	{
		svec->sprite_x = info->sprite[info->s_order[i]].x - info->player.pos_x;
		svec->sprite_y = info->sprite[info->s_order[i]].y - info->player.pos_y;
		svec->invdet = 1.0 / (info->player.plane_x * info->player.dir_y
								- info->player.dir_x * info->player.plane_y);
		svec->trans_x = svec->invdet * (info->player.dir_y * svec->sprite_x
								- info->player.dir_x * svec->sprite_y);
		svec->trans_y = svec->invdet * (-info->player.plane_y * svec->sprite_x
								+ info->player.plane_x * svec->sprite_y);
		svec->screen = (int)((info->width / 2) * (1 + svec->trans_x
								/ svec->trans_y));
		scaling_sprites(info, svec);
		drawing_sprite(info, svec);
		i++;
	}
}
