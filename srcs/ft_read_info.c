/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyulee <kyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 20:36:10 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/27 07:33:12 by kyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_cubfile(char *file_name, t_info *info)
{
	char	*line;
	char	**tab;
	int		flag;

	if (!ft_isformat(file_name, ".cub"))
		ft_strexit("ERROR: CUB File Needed!");
	info->fd = open(file_name, O_RDONLY);
	if (info->fd == -1)
		ft_strexit("ERROR: No Such CUB File Available!");
	flag = 0;
	while (get_next_line(info->fd, &line) > 0)
	{
		if (line[0] != EMPTY_LINE)
		{
			tab = ft_split(line, ' ');
			if (!tab)
				ft_strexit("ERROR: Split Fail!");
			flag = decide_store_info(info, tab);
			ft_frees(tab);
			if (flag == MAP_INFO)
				break ;
		}
		free(line);
	}
	info->line = line;
}

int		decide_store_info(t_info *info, char **tab)
{
	if (ft_strcmp(tab[0], "R") == 0)
		store_display_resolution(info, tab);
	else if (ft_strcmp(tab[0], "NO") == 0)
		store_texture(info, tab, NORTH);
	else if (ft_strcmp(tab[0], "SO") == 0)
		store_texture(info, tab, SOUTH);
	else if (ft_strcmp(tab[0], "WE") == 0)
		store_texture(info, tab, WEST);
	else if (ft_strcmp(tab[0], "EA") == 0)
		store_texture(info, tab, EAST);
	else if (ft_strcmp(tab[0], "S") == 0)
		store_texture(info, tab, SPR);
	else if (ft_strcmp(tab[0], "F") == 0)
		store_color(info, tab, FLOOR);
	else if (ft_strcmp(tab[0], "C") == 0)
		store_color(info, tab, CEILING);
	else
		return (MAP_INFO);
	return (0);
}

void	store_display_resolution(t_info *info, char **tab)
{
	char	*width;
	char	*height;
	int		size_x;
	int		size_y;

	width = tab[1];
	height = tab[2];
	if (ft_dsize(tab) != 3)
		ft_strexit("ERROR: Invalid Argument Given!");
	if (!width || !height)
		ft_strexit("ERROR: Missing Resolution Info");
	if (!ft_alldigit(width) || !ft_alldigit(height))
		ft_strexit("ERROR: Not A Number Given As Resolution Info!");
	if (info->width || info->height)
		ft_strexit("ERROR:Information already exists!");
	info->width = ft_atoi(width);
	info->height = ft_atoi(height);
	mlx_get_screen_size(info->mlx, &size_x, &size_y);
	info->width = info->width > 1920 ? size_x : info->width;
	info->width = info->width < 848 ? 848 : info->width;
	info->height = info->height > 1080 ? size_y : info->height;
	info->height = info->height < 480 ? 480 : info->height;
}

void	store_texture(t_info *info, char **tab, int flag)
{
	int		fd;
	char	*xpm_path;

	xpm_path = tab[1];
	if (ft_dsize(tab) != 2)
		ft_strexit("ERROR: Invalid Argument Given!");
	if (!xpm_path || !ft_isformat(xpm_path, ".xpm"))
		ft_strexit("ERROR: Path To XPM Needed!");
	if (info->texture.path[flag])
		ft_strexit("ERROR:Information already exists!");
	fd = open(xpm_path, O_RDONLY);
	if (fd == -1)
		ft_strexit("ERROR: No Such XPM Available!");
	close(fd);
	info->texture.path[flag] = ft_strdup(xpm_path);
}

void	store_color(t_info *info, char **tab, int flag)
{
	char	**rgb;
	char	*rgb_color;
	int		hex;
	int		temp;
	int		i;

	rgb_color = tab[1];
	if (ft_dsize(tab) != 2)
		ft_strexit("ERROR: Invalid Argument Given!");
	if (!(rgb = ft_split(rgb_color, ',')))
		ft_strexit("ERROR: Split Fail!");
	i = 0;
	hex = 0;
	while (i < 3)
	{
		if (!rgb[i] || !ft_alldigit(rgb[i]))
			ft_strexit("ERROR: RGB Info Incomplete!");
		temp = ft_atoi(rgb[i]);
		if (temp > 255 || temp < 0)
			ft_strexit("ERROR: RGB Range Invalid!");
		hex = hex * 256 + temp;
		i++;
	}
	store_set_color(info, hex, flag);
	ft_frees(rgb);
}
