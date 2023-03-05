/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 01:01:37 by bel-amri          #+#    #+#             */
/*   Updated: 2023/03/05 13:55:16 by bel-amri         ###   ########.fr       */
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

int	render(t_game *game)
{
	draw_player(*game, game->minimap_player_d);
	draw_line(new_vector(new_pos(50, 50), new_pos(200, 200)));
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
	game.minimap_scale = 1;
	game.minimap_block_d = SCREEN_HEIGHT / game.map_height * game.minimap_scale;
	game.minimap_player_d = game.minimap_block_d * .15;
	game.map = "\
111111\
101011\
101111\
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
		draw_blocks(&game, game.minimap_block_d);
	else
		draw_blocks(&game, game.minimap_block_d);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
}
