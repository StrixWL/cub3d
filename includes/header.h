/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:33:06 by bel-amri          #+#    #+#             */
/*   Updated: 2023/03/21 20:57:26 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include <mlx.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include "cub3d.h"

/* variables */
# define SCREEN_HEIGHT 1080
# define SCREEN_WIDTH 1920
# define ROT_SPEED 4
# define MVT_SPEED 61
# define VIEW_RANGE 60
# define RENDER_RANGE 100000
# define DIRECTION_LEN 400000000 // 400000000
# define BLOCK_D 200
/* constants */
# define PI 3.141592653589793
# define R_RIGHT 124
# define R_LEFT 123
# define M_RIGHT 2
# define M_LEFT 0
# define M_FORWARD 13
# define M_BACKWARD 1

/* enums */
typedef enum e_boolean {FALSE, TRUE}	t_bool;
typedef enum e_direction {
	NORTH,
	SOUTH,
	EAST,
	WEST
}				t_orientation;

/* -> structs <- */
typedef struct s_pos
{
	float		x;
	float		y;
}					t_pos;
typedef struct s_vector
{
	t_pos	origin;
	t_pos	direction;
	float	heigh;
}					t_vector;
typedef struct s_img_data {
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					w;
	int					h;
}				t_img_data;
typedef struct s_pressed_keys {
	t_bool	r_right;
	t_bool	r_left;
	t_bool	m_right;
	t_bool	m_left;
	t_bool	m_forward;
	t_bool	m_backward;
}				t_pressed_keys;
typedef struct s_game
{
	void				*mlx;
	void				*win;
	t_img_data			img;
	char				*map;
	int					map_len;
	int					map_height;
	int					map_width;
	int					minimap_block_d;
	t_pressed_keys		pressed_keys;
	t_orientation		player_orientation;
	t_vector			player;
	int					player_view_angle;
	struct t_settings	*settings;
	struct s_img_data	img_no;
	struct s_img_data	img_so;
	struct s_img_data	img_ea;
	struct s_img_data	img_we;
	int					floor_color;
	int					ciel_color;
}					t_game;
typedef struct s_ray_data
{
	float			distance;
	t_orientation	orientation;
	int				intersection;
	int				code;
	t_orientation	v_orientation;
	t_orientation	h_orientation;
}				t_ray_data;

/* -> prototypes <- */
/* init */
t_img_data	*img_save(t_img_data *data);
void		init_keys(t_game *game);
void		set_player_data(t_game *game);
int			render(t_game *game);
void		init_mlx(t_game *game, int tabon);

/* keys handler */
int			key_press_handler(int keycode, t_pressed_keys *pressed_keys);
int			key_release_handler(int keycode, t_pressed_keys *pressed_keys);
void		display_pressed_buttons(t_game *game);

/* objects */
t_pos		new_pos(float x, float y);
t_vector	new_vector(t_pos origin, t_pos direction);

/* movements */
void		update_player(t_game *game);

/* raycaster */
t_ray_data	cast_ray(t_vector ray, t_game *game);
void		get_v_intersection(t_game *game, t_pos *h_intersection,
				t_vector ray, t_ray_data *data);
void		get_h_intersection(t_game *game, t_pos *h_intersection,
				t_vector ray, t_ray_data *data);
float		get_distance(t_pos p1, t_pos p2);

/* 3d rendering*/
void		draw_3d(t_game *game, t_ray_data *data);
void		put_pixel(int x, int y, int color);

/* parsing */
int			fill_img_data(t_game *game, char *s, t_img_data *img);
int			fill_imgs_data(t_game *game);
void		get_x_y_orientation(t_game *game, char *map, int width);
int			take_floor_color(t_game *game, char *s);
int			take_ciel_color(t_game *game, char *s);
void		take_parsing_infos(t_game *game, struct t_settings *settings);
int			search_quotes(char *s);

#endif
