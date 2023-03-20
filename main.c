/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 01:01:37 by bel-amri          #+#    #+#             */
/*   Updated: 2023/03/20 18:04:55 by yabidi           ###   ########.fr       */
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
			put_pixel2(x, y++, 0);
		x++;
	}
}

int	render(t_game *game)
{
	float			angle;
	float			x1;
	float			y1;
	float			i;
	int				j;
	t_ray_data		data;
	float			distance[SCREEN_WIDTH];
	char			status[SCREEN_WIDTH];
	int				intersection[SCREEN_WIDTH];
	float			w;

	w = 60 / (float)SCREEN_WIDTH;
	clear();
	update_player(game);
	i = 0;
	j = 0;
	angle = game->player_view_angle - VIEW_RANGE / 2;
	game->units_height = game->map_height * 100;
	game->units_width = game->map_width * 100;
	while (i < VIEW_RANGE)
	{
		if (angle >= 360)
			angle = angle - 360;
		x1 = DIRECTION_LEN * cos((angle) * PI / 180);
		y1 = DIRECTION_LEN * sin((angle) * PI / 180);
		data = cast_ray(new_vector(game->player.origin, new_pos(game->player.origin.x + x1, game->player.origin.y + y1)), game);
		distance[j] = data.distance * (cos((i - 30) * PI / 180)) ;
		status[j] = data.orientation;
		intersection[j] = data.intersection;
		angle += w;
		i += w;
		j++;
	}
	draw_3d(game, distance, status, intersection);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	display_pressed_buttons(game);
	return (0);
}
 // NORTH SOUTH
// EAST WEST

int	main(int argc, char **argv)
{
	t_game		game;
	t_settings	*settings;
	t_settings	*temp;

	(void)argc;
	game.mlx = mlx_init();
	/* parsing */
	settings = new_node_settings();
	if (parsing(argv[1], settings) == -1)
		return (-1);
	temp = settings;
	while (temp->next)
		temp = temp->next;
	game.map = temp->value;
	game.map_height = ft_strlen(temp->value) / temp->size;
	game.map_width = temp->size;
	game.units_height = game.map_height * 100;
	game.units_width = game.map_width * 100;
	get_x_y_orientation(&game, temp->value, temp->size);
	printf("%d\n", getpid());
	game.map_len = ft_strlen(game.map);
	game.settings = settings;
	if (fill_imgs_data(&game) == -1)
		return (-1);
	/* graphics */
	game.win = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	mlx_hook(game.win, 2, 0, &key_press_handler, &game.pressed_keys);
	mlx_hook(game.win, 3, 0, &key_release_handler, &game.pressed_keys);
	mlx_loop_hook(game.mlx, render, &game);
	game.img.img = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel,
					&game.img.line_length, &game.img.endian);
	img_save(&game.img);
	game.minimap_block_d = 100;
	game.player.origin.x = game.player.origin.x * game.minimap_block_d + game.minimap_block_d / 2;
	game.player.origin.y = game.player.origin.y * game.minimap_block_d + game.minimap_block_d / 2;
	game.player.direction.x = game.player.origin.x;
	game.player.direction.y = game.player.origin.y;
	if (game.player_orientation == NORTH)
		game.player.direction.y -= DIRECTION_LEN;
	else if (game.player_orientation == SOUTH)
		game.player.direction.y += DIRECTION_LEN;
	else if (game.player_orientation == EAST)
		game.player.direction.x += DIRECTION_LEN;
	else if (game.player_orientation == WEST)
		game.player.direction.x -= DIRECTION_LEN;
	if (game.player_orientation == NORTH)
		game.player_view_angle = 270;
	else if (game.player_orientation == SOUTH)
		game.player_view_angle = 90;
	else if (game.player_orientation == EAST)
		game.player_view_angle = 0;
	else if (game.player_orientation == WEST)
		game.player_view_angle = 180;
	game.pressed_keys.r_right = FALSE;
	game.pressed_keys.r_left = FALSE;
	game.pressed_keys.m_right = FALSE;
	game.pressed_keys.m_left = FALSE;
	game.pressed_keys.m_forward = FALSE;
	game.pressed_keys.m_backward = FALSE;
	mlx_loop(game.mlx);
}


// read file name from argv (done)
// add esc botton 
// replace perror (done)
// convert the floor and ceil to int (done)
// check  on f_c color (done)
// empty map (done)
// while (s)
// check leaks in errors (map and elems)