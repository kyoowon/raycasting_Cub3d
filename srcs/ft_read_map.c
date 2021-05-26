/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyulee <kyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:21:50 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/27 07:33:15 by kyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	read_map(t_info *info, char *line)
{
	info->lstmap = ft_lstnew(ft_strdup(line));
	free(line);
	while (get_next_line(info->fd, &line) >= 0)
	{
		if (line[0] == EMPTY_LINE)
			break ;
		ft_lstadd_back(&info->lstmap, ft_lstnew(ft_strdup(line)));
		free(line);
	}
	free(line);
	close(info->fd);
	allocate_map(info, info->lstmap);
	store_map_array(info, info->lstmap);
	ft_lstclear(&(info->lstmap), free);
}

void	allocate_map(t_info *info, t_list *curr)
{
	int		y;
	int		x;

	info->map.mwidth = ft_lstsize(curr);
	info->map.mheight = ft_lstlongestsize(curr);
	if (!(info->map.map = malloc(sizeof(char *)
								* (info->map.mwidth + 1))))
		ft_strexit("ERROR: Malloc Fail!");
	info->map.map[info->map.mwidth] = NULL;
	y = 0;
	while (curr)
	{
		if (!(info->map.map[y] = malloc(sizeof(char)
								* (info->map.mheight + 1))))
			ft_strexit("ERROR: Malloc Fail!");
		x = 0;
		while (x < info->map.mheight)
		{
			info->map.map[y][x] = ' ';
			x++;
		}
		info->map.map[y][info->map.mheight] = '\0';
		y++;
		curr = curr->next;
	}
}

void	store_map_array(t_info *info, t_list *curr)
{
	int		i;
	int		j;
	char	*content;

	i = 0;
	while (i < info->map.mwidth)
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
	info->player.pos_x = i;
	info->player.pos_y = j;
	info->player.dir_x = -1.0;
	info->player.dir_y = 0.0;
	info->player.plane_x = 0.0;
	info->player.plane_y = 0.66;
	info->player.m_speed = 0.07;
	info->player.r_speed = 0.07;
	info->player.pos_x = 0.5f + i;
	info->player.pos_y = 0.5f + j;
}
