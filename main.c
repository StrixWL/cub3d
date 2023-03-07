/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 01:01:37 by bel-amri          #+#    #+#             */
/*   Updated: 2023/03/07 05:51:07 by bel-amri         ###   ########.fr       */
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

void	clear(void)
{
	int		x;
	int		y;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT)
			put_pixel(x, y++, 0);
		x++;
	}
}

int	key_press_handler(int keycode, t_pressed_keys *pressed_keys)
{
	if (keycode == R_LEFT)
		pressed_keys->r_left = TRUE;
	if (keycode == R_RIGHT)
		pressed_keys->r_right = TRUE;
	if (keycode == M_FORWARD)
		pressed_keys->m_forward = TRUE;
	if (keycode == M_BACKWARD)
		pressed_keys->m_backward = TRUE;
	if (keycode == M_LEFT)
		pressed_keys->m_left = TRUE;
	if (keycode == M_RIGHT)
		pressed_keys->m_right = TRUE;
	return (0);
}

int	key_release_handler(int keycode, t_pressed_keys *pressed_keys)
{
	if (keycode == R_LEFT)
		pressed_keys->r_left = FALSE;
	if (keycode == R_RIGHT)
		pressed_keys->r_right = FALSE;
	if (keycode == M_FORWARD)
		pressed_keys->m_forward = FALSE;
	if (keycode == M_BACKWARD)
		pressed_keys->m_backward = FALSE;
	if (keycode == M_LEFT)
		pressed_keys->m_left = FALSE;
	if (keycode == M_RIGHT)
		pressed_keys->m_right = FALSE;
	return (0);
}

void	update_player_vector(t_game *game)
{
	int		x1;
	int		y1;

	if (game->pressed_keys.r_left)
	{
		game->player_view_angle -= ROT_SPEED;
		x1 = round(DIRECTION_LEN * cos(game->player_view_angle * PI / 180));
        y1 = round(DIRECTION_LEN * sin(game->player_view_angle * PI / 180));
		game->player_vector.direction.x = game->player_vector.origin.x + x1;
		game->player_vector.direction.y = game->player_vector.origin.y + y1;
	}
	if (game->pressed_keys.r_right)
	{
		game->player_view_angle += ROT_SPEED;
		x1 = round(DIRECTION_LEN * cos(game->player_view_angle * PI / 180));
        y1 = round(DIRECTION_LEN * sin(game->player_view_angle * PI / 180));
		game->player_vector.direction.x = game->player_vector.origin.x + x1;
		game->player_vector.direction.y = game->player_vector.origin.y + y1;
	}
	if (game->pressed_keys.m_forward)
	{
		x1 = round(MVT_SPEED * sin((90 - game->player_view_angle) * PI / 180));
		y1 = round(MVT_SPEED * cos((90 - game->player_view_angle) * PI / 180));
		game->player_vector.origin.x += x1;
		game->player_vector.origin.y += y1;
		game->player_vector.direction.x += x1;
		game->player_vector.direction.y += y1;
	}
	if (game->pressed_keys.m_backward)
	{
		x1 = round(MVT_SPEED * sin((90 - game->player_view_angle) * PI / 180));
		y1 = round(MVT_SPEED * cos((90 - game->player_view_angle) * PI / 180));
		game->player_vector.origin.x -= x1;
		game->player_vector.origin.y -= y1;
		game->player_vector.direction.x -= x1;
		game->player_vector.direction.y -= y1;
	}
	if (game->pressed_keys.m_left)
	{
		x1 = round(MVT_SPEED * cos((90 - game->player_view_angle) * PI / 180));
		y1 = round(MVT_SPEED * sin((90 - game->player_view_angle) * PI / 180));
		game->player_vector.origin.x += x1;
		game->player_vector.origin.y -= y1;
		game->player_vector.direction.x += x1;
		game->player_vector.direction.y -= y1;
	}
	if (game->pressed_keys.m_right)
	{
		x1 = round(MVT_SPEED * cos((90 - game->player_view_angle) * PI / 180));
		y1 = round(MVT_SPEED * sin((90 - game->player_view_angle) * PI / 180));
		game->player_vector.origin.x -= x1;
		game->player_vector.origin.y += y1;
		game->player_vector.direction.x -= x1;
		game->player_vector.direction.y += y1;
	}
}

int	render(t_game *game)
{
	clear();
	update_player_vector(game);
	draw_blocks(game, game->minimap_block_d);
	draw_player(*game, game->minimap_player_d);
	draw_line(game->player_vector);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

int	main(void)
{
	t_game	game;

	/* parsing */
	game.map_height = 8; // 8, 4
	game.map_width = 6; // 6, 22
	game.player_vector.origin.x = 4; // player x position
	game.player_vector.origin.y = 4; // player y position
	game.player_orientation = WEST;
	game.map = "\
111111\
101011\
101111\
100011\
100001\
100001\
100001\
111111";
printf("%s\n", game.map);
// 	game.map = "\
// 1111111111111111111111\
// 1000000000000000000001\
// 1000000000000000000001\
// 1111111111111111111111";
	/* graphics */
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	game.img.img = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel,
					&game.img.line_length, &game.img.endian);
	img_save(&game.img);
	if (game.map_height > game.map_width)
		game.minimap_block_d = SCREEN_HEIGHT / game.map_height;
	else
		game.minimap_block_d = SCREEN_WIDTH / game.map_width;
	game.minimap_player_d = game.minimap_block_d * MINIMAP_PLAYER_SCALE; // .35
	game.player_vector.origin.x = game.player_vector.origin.x * game.minimap_block_d + game.minimap_block_d / 2;
	game.player_vector.origin.y = game.player_vector.origin.y * game.minimap_block_d + game.minimap_block_d / 2;
	game.player_vector.direction.x = game.player_vector.origin.x;
	game.player_vector.direction.y = game.player_vector.origin.y;
	if (game.player_orientation == NORTH)
		game.player_vector.direction.y -= DIRECTION_LEN;
	else if (game.player_orientation == SOUTH)
		game.player_vector.direction.y += DIRECTION_LEN;
	else if (game.player_orientation == EAST)
		game.player_vector.direction.x += DIRECTION_LEN;
	else if (game.player_orientation == WEST)
	{
		game.player_vector.direction.x -= DIRECTION_LEN;
		game.player_view_angle = 180;
	}
	game.pressed_keys.r_right = FALSE;
	game.pressed_keys.r_left = FALSE;
	game.pressed_keys.m_right = FALSE;
	game.pressed_keys.m_left = FALSE;
	game.pressed_keys.m_forward = FALSE;
	game.pressed_keys.m_backward = FALSE;
	mlx_hook(game.win, 2, 0, &key_press_handler, &game.pressed_keys);
	mlx_hook(game.win, 3, 0, &key_release_handler, &game.pressed_keys);
	// mlx_key_hook(game.win, keys_handler, &game);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
}
