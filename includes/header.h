/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:33:06 by bel-amri          #+#    #+#             */
/*   Updated: 2023/03/08 09:34:05 by bel-amri         ###   ########.fr       */
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

# define SCREEN_HEIGHT 512
# define SCREEN_WIDTH 1024
# define MINIMAP_SCALE 1
# define MINIMAP_PLAYER_SCALE .2
# define DIRECTION_LEN 30
# define PI 3.141592653589793

# define R_RIGHT 124
# define R_LEFT 123
# define M_RIGHT 2
# define M_LEFT 0
# define M_FORWARD 13
# define M_BACKWARD 1

# define ROT_SPEED 5
# define MVT_SPEED 3
# define VIEW_RANGE 30

/* enums */
typedef enum e_boolean {FALSE, TRUE, ZAB}	t_bool;
typedef enum e_direction {
	NORTH,
	SOUTH,
	EAST,
	WEST
}				t_direction;
/* 7it 3arfek 7mar
	NORTH: LFO9
	SOUTH: LTE7T
	WEST: LISER
	EAST: LIMEN
*/

/* -> structs <- */
typedef struct s_pos
{
	int		x;
	int		y;
}					t_pos;
typedef struct s_vector
{
	t_pos	origin;
	t_pos	direction;
}					t_vector;
typedef struct s_img_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
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
	void			*mlx;
	void			*win;
	t_img_data		img;
	char			*map;
	int				map_height;
	int				map_width;
	int				minimap_block_d;
	int				minimap_player_d;
	t_pressed_keys	pressed_keys;
	t_direction		player_orientation;
	t_vector		player_vector;
	int				player_view_angle;
}					t_game;

/* -> prototypes <- */
/* global */
t_img_data	*img_save(t_img_data *data);

/* minimap */
void		put_pixel(int x, int y, int color);
void		draw_square(int x, int y, int d, int color);
void		draw_blocks(t_game *game, int d);
void		draw_player(t_game game, int d);
void		draw_line(t_vector line, int color);

/* objects */
t_pos		new_pos(int x, int y);
t_vector	new_vector(t_pos origin, t_pos direction);

#endif