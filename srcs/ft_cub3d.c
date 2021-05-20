/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 16:06:30 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/20 17:49:58 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	main_loop(t_info *info)
{
	calc(info);
	return (0);
}

void init_info(t_info *info)
{
	info->width = 0;
	info->height = 0;
	ft_memset(info->texture.path, 0, 6);
	info->texture.floor = -1;
	info->texture.ceiling = -1;
	info->map.map = NULL;
	info->map.mapwidth = 0;
	info->map.mapheight = 0;
	info->player.dir = '\0';
	info->sprite = NULL;
	info->num_sprite = 0;
	info->buf = NULL;
	info->zBuffer = NULL;
}

int		main(int argc, char *argv[])
{
	t_info info;
	int save;

	validate_arguments(argc, argv[2], &save);
	init_info(&info);
	open_cub(argv[1], &info);
	open_cubfile(&info);
	validate_info(&info);
	read_map(&info, info.line);
	validate_map(&info);
	rearrange_all(&info);
	// mlx_loop_hook(info.mlx, &main_loop, &info);
	// mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_loop(info.mlx);
}

void	open_cub(char *file_name, t_info *info)
{
	if (!ft_isformat(file_name, ".cub"))
		ft_strexit("ERROR: CUB File Needed!");
	info->fd = open(file_name, O_RDONLY);
	if (info->fd == -1)
		ft_strexit("ERROR: No Such CUB File Available!");
}