/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 01:01:37 by bel-amri          #+#    #+#             */
/*   Updated: 2023/03/21 18:39:09 by bel-amri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.h>

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

int	render(t_game *game)
{
	float			angle;
	float			x1;
	float			y1;
	float			i;
	int				j;
	t_ray_data		data[SCREEN_WIDTH];
	float			w;

	w = 60 / (float)SCREEN_WIDTH;
	clear();
	update_player(game);
	i = 0;
	j = 0;
	angle = game->player_view_angle - VIEW_RANGE / 2;
	while (i < VIEW_RANGE)
	{
		if (angle >= 360)
			angle = angle - 360;
		x1 = DIRECTION_LEN * cos((angle) * PI / 180);
		y1 = DIRECTION_LEN * sin((angle) * PI / 180);
		data[j] = cast_ray(new_vector(game->player.origin, new_pos(game->player.origin.x + x1, game->player.origin.y + y1)), game);
		data[j].distance = data[j].distance * (cos((i - 30) * PI / 180));
		angle += w;
		i += w;
		j++;
	}
	draw_3d(game, data);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	display_pressed_buttons(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game		game;
	t_settings	*settings;
	t_settings	*temp;

	(void)argc;
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	mlx_hook(game.win, 2, 0, &key_press_handler, &game.pressed_keys);
	mlx_hook(game.win, 3, 0, &key_release_handler, &game.pressed_keys);
	mlx_loop_hook(game.mlx, render, &game);
	game.img.img = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel,
					&game.img.line_length, &game.img.endian);
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
	get_x_y_orientation(&game, temp->value, temp->size);
	printf("%d\n", getpid());
	game.map_len = ft_strlen(game.map);
	game.settings = settings;
	if (fill_imgs_data(&game) == -1)
		return (-1);
	/* graphics */
	img_save(&game.img);
	set_player_data(&game);
	mlx_loop(game.mlx);
}
