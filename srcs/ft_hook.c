/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 13:54:56 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/19 17:54:43 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int			key_press(int key, t_info *info)
{
	double oldDirX = info->player.dirX;
	double oldPlaneX = info->player.planeX;

	if (key == K_W)
	{
		if (!info->map.map[(int)(info->player.posX + info->player.dirX * info->player.moveSpeed)][(int)(info->player.posY)])
			info->player.posX += info->player.dirX * info->player.moveSpeed;
		if (!info->map.map[(int)(info->player.posX)][(int)(info->player.posY + info->player.dirY * info->player.moveSpeed)])
			info->player.posY += info->player.dirY * info->player.moveSpeed;
	}
	if (key == K_S)
	{
		if (!info->map.map[(int)(info->player.posX - info->player.dirX * info->player.moveSpeed)][(int)(info->player.posY)])
			info->player.posX -= info->player.dirX * info->player.moveSpeed;
		if (!info->map.map[(int)(info->player.posX)][(int)(info->player.posY - info->player.dirY * info->player.moveSpeed)])
			info->player.posY -= info->player.dirY * info->player.moveSpeed;
	}
	if (key == K_D)
	{
		info->player.dirX = info->player.dirX * cos(-info->player.rotSpeed) - info->player.dirY * sin(-info->player.rotSpeed);
		info->player.dirY = oldDirX * sin(-info->player.rotSpeed) + info->player.dirY * cos(-info->player.rotSpeed);
		info->player.planeX = info->player.planeX * cos(-info->player.rotSpeed) - info->player.planeY * sin(-info->player.rotSpeed);
		info->player.planeY = oldPlaneX * sin(-info->player.rotSpeed) + info->player.planeY * cos(-info->player.rotSpeed);
	}
	if (key == K_A)
	{
		info->player.dirX = info->player.dirX * cos(info->player.rotSpeed) - info->player.dirY * sin(info->player.rotSpeed);
		info->player.dirY = oldDirX * sin(info->player.rotSpeed) + info->player.dirY * cos(info->player.rotSpeed);
		info->player.planeX = info->player.planeX * cos(info->player.rotSpeed) - info->player.planeY * sin(info->player.rotSpeed);
		info->player.planeY = oldPlaneX * sin(info->player.rotSpeed) + info->player.planeY * cos(info->player.rotSpeed);
	}
	if (key == K_ESC)
		exit(0);
	return (0);
}
