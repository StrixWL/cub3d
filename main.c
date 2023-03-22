/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 01:01:37 by bel-amri          #+#    #+#             */
/*   Updated: 2023/03/22 10:02:37 by yabidi           ###   ########.fr       */
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

void	cast_rays(t_game *game, t_ray_data	*data, float angle)
{
	float	x1;
	float	y1;
	float	i;
	int		j;
	float	w;

	w = 60 / (float)SCREEN_WIDTH;
	i = 0;
	j = 0;
	angle = game->player_view_angle - VIEW_RANGE / 2;
	while (i < VIEW_RANGE)
	{
		if (angle >= 360)
			angle = angle - 360;
		x1 = DIRECTION_LEN * cos((angle) * PI / 180);
		y1 = DIRECTION_LEN * sin((angle) * PI / 180);
		data[j] = cast_ray(new_vector(game->player.origin,
					new_pos(game->player.origin.x + x1,
						game->player.origin.y + y1)), game);
		data[j].distance = data[j].distance * (cos((i - 30) * PI / 180));
		angle += w;
		i += w;
		j++;
	}
}

int	render(t_game *game)
{
	float			angle;
	t_ray_data		data[SCREEN_WIDTH];

	clear();
	update_player(game);
	angle = game->player_view_angle - VIEW_RANGE / 2;
	cast_rays(game, data, angle);
	draw_3d(game, data);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	display_pressed_buttons(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game		game;
	t_settings	*settings;

	init_mlx(&game, argc);
	settings = new_node_settings();
	if (parsing(argv[1], settings) == -1)
		return (-1);
	take_parsing_infos(&game, settings);
	if (fill_imgs_data(&game) == -1)
		return (-1);
	set_player_data(&game);
	init_keys(&game);
	mlx_loop(game.mlx);
}
