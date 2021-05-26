/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:25:45 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/26 23:51:02 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	bitmap_data(t_info *info, int fd)
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

void	bitmap_info(t_info *info, int fd)
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

void	bitmap_file(t_info *info, int fd)
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

void	save_bitmap(t_info *info)
{
	int fd;

	fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd == -1)
		ft_strexit("ERROR: No Such CUB File Available!");
	bitmap_file(info, fd);
	bitmap_info(info, fd);
	bitmap_data(info, fd);
	ft_putstr("SUCCESS: screenshot.bmp Saved!\n");
	close(fd);
	// ft_frees_nbr(info->buf);
	// ft_frees(info->map.map);
	// free(info->sprite);
	// free(info->s_order);
	// free(info->s_distance);
	// free(info->zbuffer);
	// mlx_destroy_image(info->mlx, info->img.img);
	exit(0);
}
