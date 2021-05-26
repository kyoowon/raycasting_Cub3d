/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_info_sub.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 01:48:15 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/27 01:50:04 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	store_set_color(t_info *info, int hex, int flag)
{
	if (flag == FLOOR)
	{
		if (info->texture.floor != -1)
			ft_strexit("ERROR:Information already exists!");
		info->texture.floor = hex;
	}
	else if (flag == CEILING)
	{
		if (info->texture.ceiling != -1)
			ft_strexit("ERROR:Information already exists!");
		info->texture.ceiling = hex;
	}
}
