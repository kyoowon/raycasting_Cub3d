/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyulee <kyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 21:22:12 by kyulee            #+#    #+#             */
/*   Updated: 2021/01/10 18:19:48 by kyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** factor - backup : String to copy. tmp : Initialization value.
** return - void.
** function - free the memory.
*/

void	backup_free(char **backup, char *tmp)
{
	free(*backup);
	*backup = tmp;
}

/*
** factor - backup : keep string, line : String delimited by '\n'.
** point - position of '\n'.
** return - return - 1 : String with backup, 0:String with no backup, -1: error.
** function - read the string, and return the lines
*/

int		return_lines(char **backup, char **line, char *point)
{
	char	*temp;
	int		len;

	if (*backup && (point = ft_strchr(*backup, '\n')) != NULL)
	{
		*point = '\0';
		*line = ft_strdup(*backup);
		len = ft_strlen(point + 1);
		if (len == 0)
		{
			backup_free(&(*backup), 0);
			return (1);
		}
		temp = ft_strdup(point + 1);
		backup_free(&(*backup), temp);
		return (1);
	}
	else if (*backup)
	{
		*line = *backup;
		*backup = 0;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

/*
** factor - fd : file descriptor. line : String delimited by '\n'.
** return - 1 : String with backup, 0:String with no backup, -1: error.
** function - read the string, and return the lines
*/

int		get_next_line(int fd, char **line)
{
	static char	*stack[OPEN_MAX];
	char		buff[BUFFER_SIZE + 1];
	int			read_size;
	char		*temp;
	char		*point;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	while ((read_size = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[read_size] = '\0';
		temp = ft_strjoin(stack[fd], buff);
		free(stack[fd]);
		stack[fd] = temp;
		if ((point = ft_strchr(stack[fd], '\n')) != NULL)
			return (return_lines(&stack[fd], line, point));
	}
	if (read_size < 0)
		return (-1);
	return (return_lines(&stack[fd], line, point));
}
