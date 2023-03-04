/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 21:00:23 by bel-amri          #+#    #+#             */
/*   Updated: 2023/03/04 21:31:38 by bel-amri         ###   ########.fr       */
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
	int		deltaX;
	int		deltaY;

	
}

void	draw_square(int x, int y, int d)
{
	int		x_m;
	int		y_m;

	x_m = x + d;
	y_m = y + d;
	while (x < x_m)
	{
		y = y_m - d;
		while (y < y_m)
			put_pixel(x, y++, 0xFF0000);
		x++;
	}
}
