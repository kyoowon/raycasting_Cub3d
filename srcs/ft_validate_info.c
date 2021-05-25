/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:49:30 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/25 22:23:24 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	validate_arguments(int argc, char *option, int *save)
{
	if (argc > 3)
		ft_strexit("ERROR: Too Many Arguments Given!");
	if (argc < 2)
		ft_strexit("ERROR: Too Few Arguments Given!");
	if (argc == 2)
		*save = OFF;
	else if (ft_strcmp(option, "--save") == 0)
		*save = ON;
	else
		ft_strexit("ERROR: Invalid Argument Given!");
}

void	validate_info(t_info *info)
{
	if (!info->width || !info->height)
		ft_strexit("ERROR: Resolution Info Missing");
	if (!info->texture.path[NORTH] || !info->texture.path[SOUTH]
		|| !info->texture.path[WEST] || !info->texture.path[EAST]
		|| !info->texture.path[SPR]
		|| info->texture.floor == -1 || info->texture.ceiling == -1)
		ft_strexit("ERROR: Texture Info Missing");
}

void	validate_map(t_info *info)
{
	if (!info->map.mwidth || !info->map.mheight)
		ft_strexit("ERROR: Invalid Map Parsing");
	if (info->player.dir == '\0')
		ft_strexit("ERROR: No Player Position Given!");
	validate_map_horizontal(info->map.map, info->map.mwidth, info->map.mheight);
	validate_map_vertical(info->map.map, info->map.mwidth, info->map.mheight);
}

void	validate_map_horizontal(char **map, int width, int height)
{
	int	x;
	int	y;

	y = 0;
	while (y < width)
	{
		if (map[y][0] != ' ' && map[y][0] != WALL)
			ft_strexit("ERROR: Map Not Surronded By Walls! (Left Side)");
		x = 1;
		while (x < height)
		{
			while (x < height && map[y][x] == ' ')
				x++;
			if (x == height)
				break ;
			if (map[y][x - 1] == ' ' && map[y][x] != WALL)
				ft_strexit("ERROR: Map Not Surronded By Walls! (Left Side)");
			while (x < height && map[y][x] != ' ')
				x++;
			if (map[y][x - 1] != WALL)
				ft_strexit("ERROR: Map Not Surronded By Walls! (Right Side)");
		}
		y++;
	}
}

void	validate_map_vertical(char **map, int width, int height)
{
	int	x;
	int	y;

	x = 0;
	while (x < height)
	{
		if (map[0][x] != ' ' && map[0][x] != WALL)
			ft_strexit("ERROR: Map Not Surronded By Walls! (Upper Side)");
		y = 1;
		while (y < width)
		{
			while (y < width && map[y][x] == ' ')
				y++;
			if (y == width)
				break ;
			if (map[y - 1][x] == ' ' && map[y][x] != WALL)
				ft_strexit("ERROR: Map Not Surronded By Walls! (Upper Side)");
			while (y < width && map[y][x] != ' ')
				y++;
			if (map[y - 1][x] != WALL)
				ft_strexit("ERROR: Map Not Surronded By Walls! (Bottom Side)");
		}
		x++;
	}
}
