/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 20:36:10 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/20 18:03:39 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	open_cubfile(t_info *info)
{
	char	*line;
	char	**tab;
	int		flag;

	flag = 0;
	while (get_next_line(info->fd, &line) > 0)
	{
		if (line[0] == '\0')
			continue;
		tab = ft_split(line, ' ');
		if (!tab)
			ft_strexit("ERROR: Split Fail!");
		flag = decide_what_to_store(info, tab);
		ft_frees(tab);
		if (flag == MAP_START)
			break ;
		ft_printf("%s \n", line);
		free(line);
	}
	info->line = line;
}

int		decide_what_to_store(t_info *info, char **tab)
{
	if (ft_strcmp(tab[0], "R") == 0)
		store_resolution(info, tab[1], tab[2]);
	else if (ft_strcmp(tab[0], "NO") == 0)
		store_texture(info, tab[1], NORTH);
	else if (ft_strcmp(tab[0], "SO") == 0)
		store_texture(info, tab[1], SOUTH);
	else if (ft_strcmp(tab[0], "WE") == 0)
		store_texture(info, tab[1], WEST);
	else if (ft_strcmp(tab[0], "EA") == 0)
		store_texture(info, tab[1], EAST);
	else if (ft_strcmp(tab[0], "S") == 0)
		store_texture(info, tab[1], SPR);
	else if (ft_strcmp(tab[0], "F") == 0)
		store_color(info, tab[1], FLOOR);
	else if (ft_strcmp(tab[0], "C") == 0)
		store_color(info, tab[1], CEILING);
	else
		return (MAP_START);
	return (0);
}

void	store_resolution(t_info *info, char *width, char *height)
{
	if (!width || !height)
		ft_strexit("ERROR: Missing Resolution Info");
	if (!ft_alldigit(width) || !ft_alldigit(height))
		ft_strexit("ERROR: Not A Number Given As Resolution Info");
	info->width = ft_atoi(width);
	info->height = ft_atoi(height);
	info->width = info->width > 1920 ? 1920 : info->width;
	info->width = info->width < 848 ? 848 : info->width;
	info->height = info->height > 1080 ? 1080 : info->height;
	info->height = info->height < 480 ? 480 : info->height;
}

void	store_texture(t_info *info, char *xpm_path, int flag)
{
	int		fd;

	if (!xpm_path || !ft_isformat(xpm_path, ".xpm"))
		ft_strexit("ERROR: Path To XPM Needed!");
	fd = open(xpm_path, O_RDONLY);
	if (fd == -1)
		ft_strexit("ERROR: No Such XPM Available!");
	close(fd);
	info->texture.path[flag] = ft_strdup(xpm_path);
}

void	store_color(t_info *info, char *rgb_with_comma, int flag)
{
	char	**rgb;
	int		hex;
	int		temp;
	int		i;

	if (!(rgb = ft_split(rgb_with_comma, ',')))
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
	if (flag == FLOOR)
		info->texture.floor = hex;
	else if (flag == CEILING)
		info->texture.ceiling = hex;
	ft_frees(rgb);
}