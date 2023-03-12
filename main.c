/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 01:01:37 by bel-amri          #+#    #+#             */
/*   Updated: 2023/03/12 10:35:47 by bel-amri         ###   ########.fr       */
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

t_bool	is_wall(t_game *game, t_pos cord)
{
	int		wall_x;
	int		wall_y;

	wall_x = cord.x / game->minimap_block_d;
	wall_y = cord.y / game->minimap_block_d;
	if (wall_x + wall_y * game->map_width > strlen(game->map))
		return (FALSE);
	if (game->map[(wall_x + wall_y * game->map_width)] == '1')
		return (TRUE);
	return (FALSE);
}

void	update_player_vector(t_game *game)
{
	float		x1;
	float		y1;
	int			x_gap;
	int			y_gap;
	int			gap;

	gap = 12;
	x_gap = 0;
	y_gap = 0;
	if (game->player_view_angle > 0 && game->player_view_angle < 180) // looking down
		y_gap = -gap;
	if (game->player_view_angle > 180 && game->player_view_angle < 360) // looking up
		y_gap = gap;
	if (game->player_view_angle > 90 && game->player_view_angle < 270) // looking left
		x_gap = gap;
	else // looking right
		x_gap = -gap;
	if (game->pressed_keys.r_left)
	{
		game->player_view_angle -= ROT_SPEED;
		if (game->player_view_angle < 0)
			game->player_view_angle = 360 - abs(game->player_view_angle);
		x1 = DIRECTION_LEN * cos(game->player_view_angle * PI / 180);
        y1 = DIRECTION_LEN * sin(game->player_view_angle * PI / 180);
		game->player_vector.direction.x = game->player_vector.origin.x + x1;
		game->player_vector.direction.y = game->player_vector.origin.y + y1;
	}
	if (game->pressed_keys.r_right)
	{
		game->player_view_angle += ROT_SPEED;
		if (game->player_view_angle >= 360)
			game->player_view_angle = game->player_view_angle - 360;
		x1 = DIRECTION_LEN * cos(game->player_view_angle * PI / 180);
        y1 = DIRECTION_LEN * sin(game->player_view_angle * PI / 180);
		game->player_vector.direction.x = game->player_vector.origin.x + x1;
		game->player_vector.direction.y = game->player_vector.origin.y + y1;
	}
	if (game->pressed_keys.m_forward)
	{
		x1 = MVT_SPEED * sin((90 - game->player_view_angle) * PI / 180);
		y1 = MVT_SPEED * cos((90 - game->player_view_angle) * PI / 180);
		if (!is_wall(game, new_pos(game->player_vector.origin.x, game->player_vector.origin.y + y1)))
		{
			game->player_vector.origin.y += y1;
			game->player_vector.direction.y += y1;
		}
		if (!is_wall(game, new_pos(game->player_vector.origin.x + x1, game->player_vector.origin.y)))
		{
			game->player_vector.origin.x += x1;
			game->player_vector.direction.x += x1;
		}
	}
	if (game->pressed_keys.m_backward)
	{
		x1 = MVT_SPEED * sin((90 - game->player_view_angle) * PI / 180);
		y1 = MVT_SPEED * cos((90 - game->player_view_angle) * PI / 180);
		if (!is_wall(game, new_pos(game->player_vector.origin.x + x_gap, game->player_vector.origin.y + y1 + y_gap)))
		{
			game->player_vector.origin.x -= x1;
			game->player_vector.direction.x -= x1;

		}
		if (!is_wall(game, new_pos(game->player_vector.origin.x + x1 + x_gap, game->player_vector.origin.y + y_gap)))
		{
			game->player_vector.origin.y -= y1;
			game->player_vector.direction.y -= y1;
		}
	}
	if (game->pressed_keys.m_left)
	{
		x1 = MVT_SPEED * cos((90 - game->player_view_angle) * PI / 180);
		y1 = MVT_SPEED * sin((90 - game->player_view_angle) * PI / 180);
		if (!is_wall(game, new_pos(game->player_vector.origin.x , game->player_vector.origin.y + y1)))
		{
			game->player_vector.origin.x += x1;
			game->player_vector.direction.x += x1;
		}
		if (!is_wall(game, new_pos(game->player_vector.origin.x + x1, game->player_vector.origin.y)))
		{
			game->player_vector.origin.y -= y1;
			game->player_vector.direction.y -= y1;
		}
	}
	if (game->pressed_keys.m_right)
	{
		x1 = MVT_SPEED * cos((90 - game->player_view_angle) * PI / 180);
		y1 = MVT_SPEED * sin((90 - game->player_view_angle) * PI / 180);
		if (!is_wall(game, new_pos(game->player_vector.origin.x , game->player_vector.origin.y + y1)))
		{
			game->player_vector.origin.x -= x1;
			game->player_vector.direction.x -= x1;
		}
		if (!is_wall(game, new_pos(game->player_vector.origin.x + x1, game->player_vector.origin.y)))
		{
			game->player_vector.origin.y += y1;
			game->player_vector.direction.y += y1;
		}
	}
}

t_bool	get_h_intersection(t_game *game, t_pos *h_intersection, t_vector ray)
{
	float	a;
	float	b;
	t_pos	delta;


	if (ray.origin.y == ray.direction.y) // parallel with x axes
		return (FALSE);
	else if (ray.origin.y > ray.direction.y) // looking up
	{
		h_intersection->y = floor(ray.origin.y / game->minimap_block_d) * game->minimap_block_d;
		while (h_intersection->y > 0)
		{
			delta.x = ray.origin.x - ray.direction.x;
			delta.y = ray.origin.y - ray.direction.y;
			if (!delta.x)
				h_intersection->x = ray.origin.x;
			else
			{
				a = delta.y / delta.x;
				b = ray.origin.y - a * ray.origin.x;
				h_intersection->x = (h_intersection->y - b) / a;
			}
			if (!is_wall(game, new_pos(h_intersection->x, h_intersection->y - game->minimap_block_d)))
				h_intersection->y -= game->minimap_block_d;
			else
				break ;
		}
	}
	else
	{
		h_intersection->y = (floor(ray.origin.y / game->minimap_block_d) * game->minimap_block_d) + game->minimap_block_d;
		while (h_intersection->y < SCREEN_HEIGHT)
		{
			delta.x = ray.origin.x - ray.direction.x;
			delta.y = ray.origin.y - ray.direction.y;
			if (!delta.x)
				h_intersection->x = ray.origin.x;
			else
			{
				a = delta.y / delta.x;
				b = ray.origin.y - a * ray.origin.x;
				h_intersection->x = (h_intersection->y - b) / a;
			}
			if (!is_wall(game, *h_intersection))
				h_intersection->y += game->minimap_block_d;
			else
				break ;
		}
	}
	if (h_intersection->y > 0 && h_intersection->y < SCREEN_HEIGHT)
		return (TRUE);
	return (FALSE);
}

t_bool	get_v_intersection(t_game *game, t_pos *h_intersection, t_vector ray)
{
	float	a;
	float	b;
	t_pos	delta;


	if (ray.origin.x == ray.direction.x) // parallel with y axes
		return (FALSE);
	else if (ray.origin.x > ray.direction.x) // looking left
	{
		h_intersection->x = floor(ray.origin.x / game->minimap_block_d) * game->minimap_block_d;
		while (h_intersection->x > 0)
		{
			delta.x = ray.origin.x - ray.direction.x;
			delta.y = ray.origin.y - ray.direction.y;
			a = delta.y / delta.x;
			b = ray.origin.y - a * ray.origin.x;
			h_intersection->y = a * h_intersection->x + b;
			if (!is_wall(game, new_pos(h_intersection->x - game->minimap_block_d, h_intersection->y)))
				h_intersection->x -= game->minimap_block_d;
			else
				break ;
		}
	}
	else
	{
		h_intersection->x = (floor(ray.origin.x / game->minimap_block_d) * game->minimap_block_d) + game->minimap_block_d;
		while (h_intersection->x < SCREEN_WIDTH)
		{
			delta.x = ray.origin.x - ray.direction.x;
			delta.y = ray.origin.y - ray.direction.y;
			a = (float)delta.y / (float)delta.x;
			b = ray.origin.y - a * ray.origin.x;
			h_intersection->y = a * h_intersection->x + b;
			if (!is_wall(game, *h_intersection))
				h_intersection->x += game->minimap_block_d;
			else
				break ;
		}
	}
	if (h_intersection->x > 0 && h_intersection->x < SCREEN_WIDTH)
		return (TRUE);
	return (FALSE);
}

int		get_distance(t_pos p1, t_pos p2)
{
	float		d;

	d = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
	return (d);
}

int	cast_ray(t_vector ray, t_game *game, int color)
{
	t_pos	h_intersection;
	t_pos	v_intersection;
	int		h_code;
	int		v_code;

	h_code = get_h_intersection(game, &h_intersection, ray);
	v_code = get_v_intersection(game, &v_intersection, ray);
	if (!h_code && v_code)
	{
		draw_line(new_vector(ray.origin, v_intersection), color);
		return (get_distance(ray.origin, v_intersection));
	}
	else if (!v_code && h_code)
	{
		draw_line(new_vector(ray.origin, h_intersection), color);
		return (get_distance(ray.origin, h_intersection));
	}
	else if (h_code && v_code)
	{
		if (get_distance(ray.origin, v_intersection) < get_distance(ray.origin, h_intersection))
		{
			draw_line(new_vector(ray.origin, v_intersection), color);
			return (get_distance(ray.origin, v_intersection));
		}
		else
		{
			draw_line(new_vector(ray.origin, h_intersection), color);
			return (get_distance(ray.origin, h_intersection));
		}
	}
	return (0);
}

int	render(t_game *game)
{
	float			angle;
	float		x1;
	float		y1;
	float			i;

	clear();
	update_player_vector(game);
	draw_blocks(game, game->minimap_block_d);
	i = 0;
	angle = game->player_view_angle - VIEW_RANGE / 2;
	while (i < VIEW_RANGE)
	{
		if (angle >= 360)
			angle = angle - 360;
		x1 = DIRECTION_LEN * cos((angle) * PI / 180);
		y1 = DIRECTION_LEN * sin((angle) * PI / 180);
		// draw_line(new_vector(game->player_vector.origin, new_pos(game->player_vector.origin.x + x1, game->player_vector.origin.y + y1)), 0xFFFFFF);
		// YOU GET RAYS DISTANCES HERE ↓↓↓↓↓
		cast_ray(new_vector(game->player_vector.origin, new_pos(game->player_vector.origin.x + x1, game->player_vector.origin.y + y1)), game, 0xFFFFFF);
		// draw_line(new_vector(game->player_vector.origin, new_pos(game->player_vector.origin.x + x1, game->player_vector.origin.y + y1)), 0xFFFFFF);
		// YOU GET RAYS DISTANCES HERE ↑↑↑↑↑
		angle += .1;
		i += .1;
	}
	draw_player(*game, game->minimap_player_d);
	cast_ray(game->player_vector, game, 0x0000FF);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

int	main(void)
{
	t_game	game;

	/* parsing */
	game.map_height = 18; // 8, 18, 18
	game.map_width = 18; // 6, 18, 220
	game.player_vector.origin.x = 4; // player x position
	game.player_vector.origin.y = 4; // player y position
	game.player_orientation = SOUTH;
	/* 7it 3arfek 7mar
		NORTH: LFO9
		SOUTH: LTE7T
		WEST: LISER
		EAST: LIMEN
	*/
	game.map = "\
111111\
101011\
101111\
100011\
100001\
100001\
101001\
111111";
printf("%d\n", getpid());
	game.map = "\
111111111111111111\
100000000000000001\
100000000000000001\
100000000000100001\
100000000001000001\
100000000000000001\
100000000000000001\
100000000000000001\
100000000000000001\
100000000000000001\
100000000000000001\
100000000000000001\
100000000000000001\
100000000000000001\
100000001000011101\
100000000000000001\
100000000000000001\
111111111111111111\
";
// 	game.map = "\
// 1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111\
// 1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001\
// 1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001\
// 1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001\
// 1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001\
// 1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001\
// 1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001\
// 1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001\
// 1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001\
// 1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001\
// 1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001\
// 1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001\
// 1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001\
// 1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001\
// 1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001\
// 1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001\
// 1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001\
// 1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
	/* graphics */
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	mlx_hook(game.win, 2, 0, &key_press_handler, &game.pressed_keys);
	mlx_hook(game.win, 3, 0, &key_release_handler, &game.pressed_keys);
	mlx_loop_hook(game.mlx, render, &game);
	game.img.img = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel,
					&game.img.line_length, &game.img.endian);
	img_save(&game.img);
	if (game.map_height >= game.map_width)
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
		game.player_vector.direction.x -= DIRECTION_LEN;
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
