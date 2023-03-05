/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:33:06 by bel-amri          #+#    #+#             */
/*   Updated: 2023/03/05 17:10:05 by bel-amri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include <mlx.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

# define SCREEN_HEIGHT 512
# define SCREEN_WIDTH 1024

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
	int			minimap_block_d;
	int			minimap_player_d;
	float		minimap_scale;
	t_pos		player_pos;
	int			map_height;
	int			map_width;
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