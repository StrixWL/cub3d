/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 21:00:23 by bel-amri          #+#    #+#             */
/*   Updated: 2023/03/13 11:06:19 by bel-amri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.h>

void	put_pixel(int x, int y, int color)
{
	t_img_data	*data;
	char		*dst;

	if (x < 0 || y < 0 || x > SCREEN_WIDTH - 1 || y > SCREEN_HEIGHT - 1)
		return ;
	x *= MINIMAP_SCALE;
	y *= MINIMAP_SCALE;
	data = img_save(NULL);
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_line_with_x(t_vector line, float a, float b, int color)
{
	float		y;

	while (floor(line.origin.x) != floor(line.direction.x))
	{
		y = a * line.origin.x + b;
		put_pixel(line.origin.x, y, color);
		if (line.origin.x < line.direction.x)
			line.origin.x++;
		else
			line.origin.x--;
	}
}

void	draw_line_with_y(t_vector line, float a, float b, int color)
{
	float		x;

	while (floor(line.origin.y) != floor(line.direction.y))
	{
		x = (line.origin.y - b) / a;
		put_pixel(x, line.origin.y, color);
		if (line.origin.y < line.direction.y)
			line.origin.y++;
		else
			line.origin.y--;
	}
}

void	draw_line(t_vector line, int color)
{
	int		delta_x;
	int		delta_y;
	float	a;
	float	b;

	delta_x = line.origin.x - line.direction.x;
	if (!delta_x)
	{
		while (floor(line.origin.y) != floor(line.direction.y))
		{
			if (line.origin.y < line.direction.y)
				line.origin.y++;
			else
				line.origin.y--;
			put_pixel(line.origin.x, line.origin.y, color);
		}
		return ;
	}
	delta_y = line.origin.y - line.direction.y;
	a = (float)delta_y / (float)delta_x;
	b = line.origin.y - a * line.origin.x;
	draw_line_with_x(line, a, b, color);
	draw_line_with_y(line, a, b, color);
}

void	draw_square(int x, int y, int d, int color)
{
	int		x_m;
	int		y_m;

	x_m = x + d;
	y_m = y + d;
	while (x < x_m)
	{
		y = y_m - d;
		while (y < y_m)
			put_pixel(x, y++, color);
		x++;
	}
}
