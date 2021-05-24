/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:21:50 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/23 23:38:04 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	read_map(t_info *info, char *line)
{
	info->lstmap = ft_lstnew(ft_strdup(line));
	free(line);
	while (get_next_line(info->fd, &line) >= 0)
	{
		if (line[0] == EMPTY_LINE)
			break;
		ft_lstadd_back(&info->lstmap, ft_lstnew(ft_strdup(line)));
		free(line);
	}
	free(line);
	allocate_map(info, info->lstmap);
	store_map_as_array(info, info->lstmap);
	ft_lstclear(&(info->lstmap), free);
}


void	allocate_map(t_info *info, t_list *curr)
{
	int		y;
	int		x;

	info->map.mapwidth = ft_lstsize(curr);
	info->map.mapheight = ft_lstlongestsize(curr);
	if (!(info->map.map = malloc(sizeof(char *) * (info->map.mapwidth + 1))))
		ft_strexit("ERROR: Malloc Fail!");
	info->map.map[info->map.mapwidth] = NULL;
	y = 0;
	while (curr)
	{
		if (!(info->map.map[y] = malloc(sizeof(char) * (info->map.mapheight + 1))))
			ft_strexit("ERROR: Malloc Fail!");
		x = 0;
		while (x < info->map.mapheight)
		{
			info->map.map[y][x] = ' ';
			x++;
		}
		info->map.map[y][info->map.mapheight] = '\0';
		y++;
		curr = curr->next;
	}
}

void	store_map_as_array(t_info *info, t_list *curr)
{
	int		i;
	int		j;
	char	*content;

	i = 0;
	while (i < info->map.mapwidth)
	{
		j = 0;
		content = (char *)curr->content;
		while (j < ft_strlen(content))
		{
			if (!ft_isset(content[j], "NSWE012 \n") && content[j] != '\0')
				ft_strexit("ERROR: Invalid Map Element Contained!");
			info->map.map[i][j] = content[j];
			if (ft_isset(content[j], "NSWE"))
				create_player(info, i, j);
			else if (content[j] == SPRITE)
				info->num_sprite++;
			j++;
		}
		curr = curr->next;
		i++;
	}
}

void	create_player(t_info *info, int i, int j)
{
	if (info->player.dir)
		ft_strexit("ERROR: Multiple Player Postions Given!");
	info->player.dir = info->map.map[i][j];
	info->player.posX = i;
	info->player.posY = j;
	info->player.dirX = -1.0;
	info->player.dirY = 0.0;
	info->player.planeX = 0.0;
	info->player.planeY = 0.66;
	info->player.moveSpeed = 0.07;
	info->player.rotSpeed = 0.07;
	info->player.posX = 0.5f + i;
	info->player.posY = 0.5f + j;
}