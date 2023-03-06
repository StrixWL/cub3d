/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:33:06 by bel-amri          #+#    #+#             */
/*   Updated: 2023/03/06 04:37:56 by bel-amri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include <mlx.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <math.h>

# define SCREEN_HEIGHT 512
# define SCREEN_WIDTH 1024
# define DIRECTION_LEN 25
# define PI 3.141592653589793
# define RIGHT 124
# define LEFT 123

/* enums */
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
typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img_data	img;
	char		*map;
	int			map_height;
	int			map_width;
	int			minimap_block_d;
	int			minimap_player_d;
	float		minimap_scale;
	t_direction	player_orientation;
	t_vector	player_vector;
	int			player_view_angle;
}					t_game;

/* -> prototypes <- */
/* global */
t_img_data	*img_save(t_img_data *data);

/* minimap */
void		put_pixel(int x, int y, int color);
void		draw_square(int x, int y, int d, int color);
void		draw_blocks(t_game *game, int d);
void		draw_player(t_game game, int d);
void		draw_line(t_vector line, float scale);

/* objects */
t_pos		new_pos(int x, int y);
t_vector	new_vector(t_pos origin, t_pos direction);

#endif