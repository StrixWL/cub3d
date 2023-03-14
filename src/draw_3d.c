/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:22:52 by yabidi            #+#    #+#             */
/*   Updated: 2023/03/14 01:20:36 by bel-amri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	put_pixel2(int x, int y, int color)
{
	t_img_data	*data;
	char		*dst;

	if (x < 0 || y < 0 || x > SCREEN_WIDTH - 1 || y > SCREEN_HEIGHT - 1)
		return ;	
	data = img_save(NULL);
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_line2(t_vector line, int color)
{
	float		delta_x;
	float		delta_y;
	float	a;
	float	b;

	delta_x = line.origin.x - line.direction.x;
	while (floor(line.origin.y) != floor(line.direction.y))
	{
		if (line.origin.y < line.direction.y)
			line.origin.y++;
		else
			line.origin.y--;
		put_pixel2(line.origin.x, line.origin.y, color);
	}
	return ;
}

void draw_3d(t_game *game, float *distance, char *status, int *intersection)
{
    int i;
    float line_heigh[SCREEN_WIDTH];
    t_vector line;

    i = 0;
	int k = 0;
    while(i < SCREEN_WIDTH)
    {
        // if (distance[i] > 60)
        //     distance[i] = 60;
        line_heigh[i] = 1000 * game->minimap_block_d / distance[i];
		// printf("%f\n", line_heigh[i]);
		if (line_heigh[i] > SCREEN_HEIGHT)
			line_heigh[i] = SCREEN_HEIGHT;
		line.origin.x = i ;
		line.origin.y = (SCREEN_HEIGHT - line_heigh[i]) / 2;
		line.direction.x = line.origin.x;
		line.direction.y = line.origin.y + line_heigh[i];
		int color = (intersection[i] + 1) * 0x00FFFF;
		if (status[i] == NORTH || status[i] == SOUTH)
			draw_line2(line, color);
		if (status[i] == WEST || status[i] == EAST)
			draw_line2(line, color);
        i++;
    }
}