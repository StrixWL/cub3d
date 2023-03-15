/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:22:52 by yabidi            #+#    #+#             */
/*   Updated: 2023/03/15 17:11:02 by yabidi           ###   ########.fr       */
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

void	draw_line2(t_game *game, t_vector line, int intersection, char *image, int line_length, int bits_per_pixel)
{
	int x_p;
	int y_p;
	int x2;
	int y2;
	int where_y;
	int	color;
	where_y = 0;
	x_p = (intersection * 100) / game->minimap_block_d;
	y_p = (where_y * 100) / line.heigh;
	y2 = (y_p * 350)/100;
	x2 = (x_p * 225)/100;
	// printf("%d\n", x2);
	color = *((int *)(image + (y2 * line_length + (x2 * bits_per_pixel / 8))));
		// printf("%d \n", intersection);
	while (line.origin.y < line.direction.y)
	{
		y2 = (y_p * 350)/100;
		line.origin.y++;
		put_pixel2(line.origin.x, line.origin.y, color);
	y_p = (where_y * 100)/ line.heigh;
	
	color = *((int *)(image + (y2 * line_length + (x2 * (bits_per_pixel / 8)))));
	
		where_y++;
	}
	return ;
}

void floor_ceil()
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (i < SCREEN_HEIGHT / 2)
	{
		k = 0;
		while (k < SCREEN_WIDTH)
		{
			put_pixel2(k, i, 0x92a1cf);
			k++;	
		}
		i++;
	}
	while (i < SCREEN_HEIGHT)
	{
		k = 0;
		while (k < SCREEN_WIDTH)
		{
			put_pixel2(k, i, 0xbdbabb);
			k++;	
		}
		i++;
	}
}

void	draw_3d(t_game *game, float *distance, char *status, int *intersection, int *code)
{
    int i;
    float line_heigh[SCREEN_WIDTH];
    t_vector line;
	void *img;
	int bits_per_pixel;
	int endian;
	int line_length;
	char *image; 
	int w = 350;
	int h = 225;
	int color;
	int i_p;
	int k_p;
	int k2;
	int i2;

    i = 0;
	int k = 0;
	img = mlx_xpm_file_to_image(game->mlx, "uk.xpm", &w, &h);
	image = mlx_get_data_addr(img, &bits_per_pixel,
					&line_length, &endian);

	floor_ceil();
	i = 0;
    while(i < SCREEN_WIDTH)
    {
        // if (distance[i] > 60)
        //     distance[i] = 60;
        line_heigh[i] = 1000 * game->minimap_block_d / distance[i];
		// printf("%f\n", line_heigh[i]);
		// if (line_heigh[i] > SCREEN_HEIGHT)
		// 	line_heigh[i] = SCREEN_HEIGHT;
		line.origin.x = i ;
		line.origin.y = (SCREEN_HEIGHT - line_heigh[i]) / 2;
		line.direction.x = line.origin.x;
		line.direction.y = line.origin.y + line_heigh[i];
		
		int color = (intersection[i] + 1) * 0x00FFFF;
		line.heigh = line_heigh[i];
		// if (status[i] == NORTH || status[i] == SOUTH)
		// if (status[i] == WEST || status[i] == EAST)
			draw_line2(game, line, intersection[i] ,image, line_length, bits_per_pixel);
		// 	draw_line2(line, color);
		// if (status[i] == NORTH || status[i] == NORTH)
			// draw_line2(line, color);
		// if (status[i] == WEST || status[i] == WEST)
		// 	draw_line2(line, color);
        i++;
    }
}