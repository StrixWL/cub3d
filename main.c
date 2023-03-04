/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 01:01:37 by bel-amri          #+#    #+#             */
/*   Updated: 2023/03/04 05:44:02 by bel-amri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.h>

t_img_data	*img_save(t_img_data *data)
{
	static t_img_data	*saved_data;

	if (!saved_data)
		saved_data = data;
	return (saved_data);
}

void	put_pixel(int x, int y, int color)
{
	t_img_data	*data;
	char		*dst;

	data = img_save(NULL);
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_square(int x, int y, int d)
{
	int		x_m;
	int		y_m;

	x_m = x + d;
	y_m = y + d;
	while (x < x_m)
	{
		y = 0;
		while (y < y_m)
			put_pixel(x, y++, 0xFF0000);
		x++;
	}
}

void	draw_blocks(t_game game, int d)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	while (game.map[i])
	{
		x = (i % game.map_width) * d;
		y = (i / game.map_width) * d;
		if (game.map[i++] == '1')
			draw_square(x, y, d);
	}
}

int	render(t_game *game)
{
	if (game->map_height > game->map_width)
		draw_blocks(*game, SCREEN_HEIGHT / game->map_height * game->minimap_scale);
	else
		draw_blocks(*game, SCREEN_WIDTH / game->map_width * game->minimap_scale);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

int	main(void)
{
	t_game	game;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	game.img.img = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel,
					&game.img.line_length, &game.img.endian);
	img_save(&game.img);
	game.map_height = 8; // 8, 4
	game.map_width = 6; // 6, 22
	game.minimap_scale = .3;
	game.map = "\
111111\
100P11\
100011\
100011\
100001\
100001\
100001\
111111";
// 	game.map = "\
// 1111111111111111111111\
// 1000000000000000000001\
// 1000000000000000000001\
// 1111111111111111111111\
// ";
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
}
