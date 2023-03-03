/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:33:06 by bel-amri          #+#    #+#             */
/*   Updated: 2023/03/03 09:19:38 by bel-amri         ###   ########.fr       */
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
typedef struct	s_img_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img_data;
typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	*map;
	double	minimap_scale;
	int		map_height;
	int		map_width;
}					t_game;

#endif