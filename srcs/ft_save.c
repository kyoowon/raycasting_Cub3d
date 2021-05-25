/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:25:45 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/25 22:56:54 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	bdata(t_info *info, int fd)
{
	int				i;
	int				j;
	unsigned char	buffer[4];

	i = info->width * (info->height - 1);
	while (i >= 0)
	{
		j = 0;
		while (j < info->width)
		{
			buffer[0] = (unsigned char)(info->img.data[i] % 256);
			buffer[1] = (unsigned char)(info->img.data[i] / 256 % 256);
			buffer[2] = (unsigned char)(info->img.data[i] / 256 / 256 % 256);
			buffer[3] = (unsigned char)(0);
			write(fd, buffer, 4);
			i++;
			j++;
		}
		i -= 2 * info->width;
	}
}

void	binfo(t_info *info, int fd)
{
	int				n;
	unsigned char	header[40];

	n = 0;
	while (n < 40)
		header[n++] = (unsigned char)(0);
	header[0] = (unsigned char)(40);
	n = info->width;
	header[4] = (unsigned char)(n % 256);
	header[5] = (unsigned char)(n / 256 % 256);
	header[6] = (unsigned char)(n / 256 / 256 % 256);
	header[7] = (unsigned char)(n / 256 / 256 / 256);
	n = info->height;
	header[8] = (unsigned char)(n % 256);
	header[9] = (unsigned char)(n / 256 % 256);
	header[10] = (unsigned char)(n / 256 / 256 % 256);
	header[11] = (unsigned char)(n / 256 / 256 / 256);
	header[12] = (unsigned char)(1);
	header[14] = (unsigned char)(32);
	write(fd, header, 40);
}

void	bfile(t_info *info, int fd)
{
	int				n;
	unsigned char	header[14];

	n = 0;
	while (n < 14)
		header[n++] = (unsigned char)(0);
	header[0] = (unsigned char)(66);
	header[1] = (unsigned char)(77);
	n = info->width * info->height * 4 + 54;
	header[2] = (unsigned char)(n % 256);
	header[3] = (unsigned char)(n / 256 % 256);
	header[4] = (unsigned char)(n / 256 / 256 % 256);
	header[5] = (unsigned char)(n / 256 / 256 / 256);
	header[10] = (unsigned char)(54);
	write(fd, header, 14);
}

int		bitmap(t_info *info)
{
	int fd;

	fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd == -1)
		ft_strexit("ERROR: No Such CUB File Available!");
	bfile(info, fd);
	binfo(info, fd);
	bdata(info, fd);
	close(fd);
	ft_putstr("success screenshot.bmp saved!\n");
	exit(1);
}
