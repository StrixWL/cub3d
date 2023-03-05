/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 21:00:23 by bel-amri          #+#    #+#             */
/*   Updated: 2023/03/05 05:56:23 by bel-amri         ###   ########.fr       */
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

void	draw_line(t_vector line)
{
	int		delta_x;
	int		delta_y;
	int		a;
	int		b;

	printf("(%d, %d) (%d, %d)\n", line.origin.x, line.origin.y, line.direction.x, line.direction.y);
	delta_x = line.origin.x - line.origin.y;
	delta_y = line.direction.y - line.direction.y;
	printf("deltaX: %d, deltaY: %d\n", delta_x, delta_y);
	a = delta_y / delta_x;
	b = line.origin.y - a * line.origin.x;
	printf("y = %dx + %d\n", a, b);
	// while (line.origin.x < line.direction.x)
	// {
	// 	while (line.origin.y < line.direction.y)
	// 	{
	// 		put_pixel(line.origin.x, line.origin.y, 0x00FF00);
	// 		line.origin.y++;
	// 	}
	// 	line.origin.x++;
	// }
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
