/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:21:50 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/20 17:27:37 by kyuwonlee        ###   ########.fr       */
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
		printf("%s\n", line);
		free(line);
	}
	free(line);
	allocate_map(info, info->lstmap);
	store_map_as_array(info, info->lstmap);
	ft_lstclear(&(info->lstmap), free);
}


void	allocate_map(t_info *info, t_list *curr)
{
	int		i;
	int		j;

	info->map.mapheight = ft_lstsize(curr);
	info->map.mapwidth = ft_lstlongestsize(curr);
	ft_printf("%d %d\n", info->map.mapheight, info->map.mapwidth);
	if (!(info->map.map = malloc(sizeof(char *) * (info->map.mapheight + 1))))
		ft_strexit("ERROR: Malloc Fail!");
	info->map.map[info->map.mapheight] = NULL;
	i = 0;
	while (curr)
	{
		if (!(info->map.map[i] = malloc(sizeof(char) * (info->map.mapwidth + 1))))
			ft_strexit("ERROR: Malloc Fail!");
		j = 0;
		while (j < info->map.mapwidth)
		{
			info->map.map[i][j] = ' ';
			j++;
		}
		info->map.map[i][info->map.mapwidth] = '\0';
		i++;
		curr = curr->next;
	}
}

void	store_map_as_array(t_info *info, t_list *curr)
{
	int		i;
	int		j;
	char	*content;

	i = 0;
	while (i < info->map.mapheight)
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
	info->player.posX = 2;
	info->player.posY = 5;
	info->player.dirX = -1.0;
	info->player.dirY = 0.0;
	info->player.planeX = 0.0;
	info->player.planeY = 0.66;
	info->player.moveSpeed = 0.07;
	info->player.rotSpeed = 0.08;
	info->player.posX = 0.5f + j;
	info->player.posY = 0.5f + i;
}