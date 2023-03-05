/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 21:00:23 by bel-amri          #+#    #+#             */
/*   Updated: 2023/03/05 12:08:18 by bel-amri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.h>

void	put_pixel(int x, int y, int color)
{
	t_img_data	*data;
	char		*dst;

	data = img_save(NULL);
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_line_with_x(int i, int j, float a, float b)
{
	int		y;

	while (i != j)
	{
		y = a * i + b;
		put_pixel(i, y, 0x00FF00);
		if (i < j)
			i++;
		else
			i--;
	}
}

void	draw_line_with_y(int i, int j, float a, float b)
{
	int		x;

	while (i != j)
	{
		x = (i - b) / a;
		put_pixel(x, i, 0x00FF00);
		if (i < j)
			i++;
		else
			i--;
	}
}

void	draw_line(t_vector line)
{
	int		delta_x;
	int		delta_y;
	float	a;
	float	b;

	delta_x = line.origin.x - line.direction.x;
	if (!delta_x)
	{
		while (line.origin.y != line.direction.y)
		{
			if (line.origin.y < line.direction.y)
				line.origin.y++;
			else
				line.origin.y--;
			put_pixel(line.origin.x, line.origin.y, 0x00FF00);
		}
		return ;
	}
	delta_y = line.origin.y - line.direction.y;
	a = (float)delta_y / (float)delta_x;
	b = line.origin.y - a * line.origin.x;
	draw_line_with_x(line.origin.x, line.direction.x, a, b);
	draw_line_with_y(line.origin.y, line.direction.y, a, b);
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
