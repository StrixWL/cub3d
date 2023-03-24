/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:22:52 by yabidi            #+#    #+#             */
/*   Updated: 2023/03/24 12:32:16 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	put_pixel(int x, int y, int color)
{
	t_img_data	*data;
	char		*dst;

	if (x < 0 || y < 0 || x > SCREEN_WIDTH || y > SCREEN_HEIGHT)
		return ;
	data = img_save(NULL);
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_line2(t_vector line,
					int intersection, t_img_data img)
{
	int	x_color;
	int	y_color;
	int	where_y;
	int	color;

	where_y = 0;
	if (line.origin.y < 0)
	{
		where_y = line.origin.y * -1;
		line.origin.y = 0;
	}
	while (line.origin.y < line.direction.y && line.origin.y < SCREEN_HEIGHT)
	{
		y_color = (((where_y * 100) / line.heigh) * (img.h)) / 100;
		x_color = (((intersection * 100)
					/ BLOCK_D) * (img.w)) / 100;
		color = *((int *)(img.addr + (y_color * img.line_length
						+ (x_color * (img.bits_per_pixel / 8)))));
		put_pixel(line.origin.x, line.origin.y, color);
		line.origin.y++;
		where_y++;
	}
	return ;
}

void	floor_ceil(t_game *game)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (i < SCREEN_HEIGHT / 2)
	{
		k = 0;
		while (k < SCREEN_WIDTH)
		{
			put_pixel(k, i, game->ciel_color);
			k++;
		}
		i++;
	}
	while (i < SCREEN_HEIGHT)
	{
		k = 0;
		while (k < SCREEN_WIDTH)
		{
			put_pixel(k, i, game->floor_color);
			k++;
		}
		i++;
	}
}

void	fill_vector_infos(t_vector *line, int i, float *line_heigh)
{
	line->origin.x = i ;
	line->origin.y = (SCREEN_HEIGHT - line_heigh[i]) / 2;
	line->direction.x = line->origin.x;
	line->direction.y = line->origin.y + line_heigh[i];
	line->heigh = line_heigh[i];
}

void	draw_3d(t_game *game, t_ray_data *data)
{
	int			i;
	float		line_heigh[SCREEN_WIDTH];
	t_vector	line;

	i = 0;
	floor_ceil(game);
	while (i < SCREEN_WIDTH)
	{
		line_heigh[i] = 2000 * BLOCK_D / data[i].distance;
		fill_vector_infos(&line, i, line_heigh);
		if (data[i].distance <= RENDER_RANGE)
		{
			if (data[i].orientation == NORTH)
				draw_line2(line, data[i].intersection, game->img_no);
			if (data[i].orientation == WEST)
				draw_line2(line, data[i].intersection, game->img_we);
			if (data[i].orientation == EAST)
				draw_line2(line, data[i].intersection, game->img_ea);
			if (data[i].orientation == SOUTH)
				draw_line2(line, data[i].intersection, game->img_so);
		}
		i++;
	}
}
