/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 16:06:30 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/01 16:15:39 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include <stdlib.h>

typedef struct s_info
{
    void *mlx;
    void *win;
    int width;
    int height;
    double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
    double	moveSpeed;
	double	rotSpeed;
}               t_info;

typedef struct s_map
{
    int width;
    int height;
    int *mapptr;
}               t_map;

int        main(void)
{
    t_info info;


    info.height = 500;
    info.width = 700;
    

	info.mlx = mlx_init();

    info.win = mlx_new_window(info.mlx, info.width, info.height, "kyulee");
    mlx_loop(info.mlx);
    return (0);
}