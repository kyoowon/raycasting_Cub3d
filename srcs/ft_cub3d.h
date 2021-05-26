/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 00:23:25 by kyuwonlee         #+#    #+#             */
/*   Updated: 2021/05/27 01:50:16 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUB3D_H
# define FT_CUB3D_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "key_press.h"
# include <math.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>

# define TEXWIDTH 64
# define TEXHEIGHT 64
# define UDIV 1
# define VDIV 1
# define VMOVE 10.0
# define ON 1
# define OFF 0
# define EMPTY_LINE '\0'
# define EMPTY '0'
# define WALL '1'
# define SPRITE '2'
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3
# define SPR 4
# define FLOOR 5
# define CEILING 6
# define MAP_INFO -1
# define PI 3.1415926535897
# define DESTROY_NOTIFY 17

typedef struct	s_img
{
	void		*img;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
	int			img_width;
	int			img_height;
}				t_img;

typedef struct	s_vec
{
	int			hit;
	int			map_x;
	int			map_y;
	int			side;
	int			step_x;
	int			step_y;
	double		pwdist;
	double		wall_x;
	double		camera;
	double		rdir_x;
	double		rdir_y;
	double		sdist_x;
	double		sdist_y;
	double		ddist_x;
	double		ddist_y;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			tex_x;
	int			tex_y;
}				t_vec;

typedef struct	s_svec
{
	double		sprite_x;
	double		sprite_y;
	double		invdet;
	double		trans_x;
	double		trans_y;
	int			screen;
	int			vmove_s;
	int			height;
	int			width;
	int			drawstart_x;
	int			drawend_x;
	int			drawstart_y;
	int			drawend_y;
	int			tex_x;
	int			tex_y;
	int			stripe;
	int			color;
}				t_svec;

typedef struct	s_texture
{
	char		*path[6];
	int			texture[6][TEXWIDTH * TEXHEIGHT];
	int			floor;
	int			ceiling;
}				t_texture;

typedef struct	s_map
{
	int			mwidth;
	int			mheight;
	char		**map;
}				t_map;

typedef struct	s_sprite
{
	double		x;
	double		y;
}				t_sprite;

typedef struct	s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		m_speed;
	double		r_speed;
	char		dir;
}				t_player;

typedef struct	s_key
{
	int			key_a;
	int			key_w;
	int			key_s;
	int			key_d;
	int			key_ar_r;
	int			key_ar_l;
	int			key_esc;
}				t_key;

typedef struct	s_info
{
	void		*mlx;
	void		*win;
	int			fd;
	int			width;
	int			height;
	int			num_sprite;
	int			**buf;
	char		*line;
	double		*zbuffer;
	t_player	player;
	t_key		key;
	t_img		img;
	t_map		map;
	t_texture	texture;
	t_sprite	*sprite;
	t_list		*lstmap;
	int			*s_order;
	double		*s_distance;
}				t_info;

typedef struct	s_pair
{
	double		first;
	int			second;
}				t_pair;

/*
** ft_cub3d.c
*/

int				main_loop(t_info *info);
void			draw_window(t_info *info);
void			draw_bitmap(t_info *info);
void			init_info(t_info *info);

/*
** ft_hook.c
*/

void			key_update(t_player *p, t_map m, t_key k, t_info *info);
int				key_press(int key, t_info *info);
int				key_release(int key, t_info *info);
void			rotate_player(t_player *p, double degree);
int				event_exit(t_info *info);

/*
** ft_read_info.c
*/

void			open_cubfile(char *file_name, t_info *info);
int				decide_store_info(t_info *info, char **tab);
void			store_display_resolution(t_info *info, char **tab);
void			store_texture(t_info *info, char **tab, int flag);
void			store_color(t_info *info, char **tab, int flag);

/*
** ft_read_info_sub.c
*/

void			store_set_color(t_info *info, int hex, int flag);

/*
** ft_read_map.c
*/

void			read_map(t_info *info, char *line);
void			allocate_map(t_info *info, t_list *curr);
void			store_map_array(t_info *info, t_list *curr);
void			create_player(t_info *info, int i, int j);

/*
** ft_save.c
*/

void			bitmap_data(t_info *info, int fd);
void			bitmap_info(t_info *info, int fd);
void			bitmap_file(t_info *info, int fd);
void			save_bitmap(t_info *info);

/*
** ft_setting.c
*/

void			setting_all(t_info *info);
void			apply_player_orientation(t_player *player);
void			allocate_buffer(t_info *info);
void			load_texture(t_info *info);
void			load_image(t_info *info, int *texture, char *path, t_img *img);

/*
** ft_wall.c
*/

void			init_dda(t_player *player, t_vec *vec);
void			calc_dda_hit(t_info *info, t_vec *vec, int *wall_type);
void			calc_perpwalldist(t_player *player, t_vec *vec, int height);
void			calc_texture_wall(t_info *info, t_vec *vec, int x, int type);
void			draw_wall(t_info *info, t_vec *vec);

/*
** ft_calc_screen.c
*/

void			draw_floor_ceiling(t_info *info);
void			sort_order(t_pair *orders, int amount);
void			sort_sprites(int *order, double *dist, int amount);
void			calc_screen(t_info *info);

/*
** ft_sprite.c
*/

void			set_malloc_sprite(t_info *info);
void			set_sprite(t_info *info);
void			scaling_sprites(t_info *info, t_svec *svec);
void			drawing_sprite(t_info *info, t_svec *svec);
void			draw_sprite(t_info *info, t_svec *svec);

/*
** ft_validate_info.c
*/

int				validate_arguments(int argc, char *option);
void			validate_info(t_info *info);
void			validate_map(t_info *info);
void			map_horizontal(char **map, int width, int height);
void			map_vertical(char **map, int width, int height);

#endif
