/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 13:54:56 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/24 16:12:57 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		key_update(t_info *info)
{
	double oldDirX = info->player.dirX;
	double oldPlaneX = info->player.planeX;
	if (info->key.key_w)
	{
		if (info->map.map[(int)(info->player.posX + info->player.dirX * info->player.moveSpeed)][(int)(info->player.posY)] != '1')
			info->player.posX += info->player.dirX * info->player.moveSpeed;
		if (info->map.map[(int)(info->player.posX)][(int)(info->player.posY + info->player.dirY * info->player.moveSpeed)] != '1')
			info->player.posY += info->player.dirY * info->player.moveSpeed;
	}
	if (info->key.key_s)
	{
		if (info->map.map[(int)(info->player.posX - info->player.dirX * info->player.moveSpeed)][(int)(info->player.posY)] != '1')
			info->player.posX -= info->player.dirX * info->player.moveSpeed;
		if (info->map.map[(int)(info->player.posX)][(int)(info->player.posY - info->player.dirY * info->player.moveSpeed)] != '1')
			info->player.posY -= info->player.dirY * info->player.moveSpeed;
	}
	if (info->key.key_d || info->key.key_ar_r)
	{
		info->player.dirX = info->player.dirX * cos(-info->player.rotSpeed) - info->player.dirY * sin(-info->player.rotSpeed);
		info->player.dirY = oldDirX * sin(-info->player.rotSpeed) + info->player.dirY * cos(-info->player.rotSpeed);
		info->player.planeX = info->player.planeX * cos(-info->player.rotSpeed) - info->player.planeY * sin(-info->player.rotSpeed);
		info->player.planeY = oldPlaneX * sin(-info->player.rotSpeed) + info->player.planeY * cos(-info->player.rotSpeed);
	}
	if (info->key.key_a || info->key.key_ar_l)
	{
		info->player.dirX = info->player.dirX * cos(info->player.rotSpeed) - info->player.dirY * sin(info->player.rotSpeed);
		info->player.dirY = oldDirX * sin(info->player.rotSpeed) + info->player.dirY * cos(info->player.rotSpeed);
		info->player.planeX = info->player.planeX * cos(info->player.rotSpeed) - info->player.planeY * sin(info->player.rotSpeed);
		info->player.planeY = oldPlaneX * sin(info->player.rotSpeed) + info->player.planeY * cos(info->player.rotSpeed);
	}
	if (info->key.key_esc)
		exit(0);
	return (0);
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