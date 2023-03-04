/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 01:01:37 by bel-amri          #+#    #+#             */
/*   Updated: 2023/03/04 02:57:41 by bel-amri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.h>


void	put_pixel(t_img_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	*create_square(t_game game, int d)
{
	t_img_data	img;
	int			x;
	int			y;
	
	img.img = mlx_new_image(game.mlx, d, d);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	x = 0;
	y = 0;
	while (x < d)
	{
		y = 0;
		while (y < d)
		{
			put_pixel(&img, x, y, 0x0000FF);
			y++;
		}
		x++;
	}
	return (img.img);
}

void	render_mini_map(t_game game, int d)
{
	void	*square;
	int		i;
	int		x;
	int		y;

	square = create_square(game, d);
	i = 0;
	while (game.map[i])
	{
		x = (i % game.map_width) * d;
		y = (i / game.map_width) * d;
		if (game.map[i] == '1')
			mlx_put_image_to_window(game.mlx, game.win, square, x, y);
		i++;
	}
}

int	main(void)
{
	t_game	game;
	void	*square;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	game.map_height = 8; // 8, 4
	game.map_width = 6; // 6, 22
	game.minimap_scale = 1;
	// 8
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
	if (game.map_height > game.map_width)
		render_mini_map(game, SCREEN_HEIGHT / game.map_height * game.minimap_scale);
	else
		render_mini_map(game, SCREEN_WIDTH / game.map_width * game.minimap_scale);
	mlx_loop(game.mlx);
}
