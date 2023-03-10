/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 01:01:37 by bel-amri          #+#    #+#             */
/*   Updated: 2023/03/10 01:53:33 by bel-amri         ###   ########.fr       */
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
		if (game->player_view_angle < 0)
			game->player_view_angle = 360 - abs(game->player_view_angle);
		x1 = round(DIRECTION_LEN * cos(game->player_view_angle * PI / 180));
        y1 = round(DIRECTION_LEN * sin(game->player_view_angle * PI / 180));
		game->player_vector.direction.x = game->player_vector.origin.x + x1;
		game->player_vector.direction.y = game->player_vector.origin.y + y1;
	}
	if (game->pressed_keys.r_right)
	{
		game->player_view_angle += ROT_SPEED;
		if (game->player_view_angle >= 360)
			game->player_view_angle = game->player_view_angle - 360;
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

t_bool	is_wall(t_game *game, t_pos cord)
{
	t_pos	wall_pos;

	wall_pos.x = cord.x / game->minimap_block_d;
	wall_pos.y = cord.y / game->minimap_block_d;
	if (game->map[wall_pos.x + wall_pos.y * game->map_width] == '1')
		return (TRUE);
	return (FALSE);
}

t_bool	get_h_intersection(t_game *game, t_pos *h_intersection, t_vector ray)
{
	float	a;
	float	b;
	t_pos	delta;


	if (ray.origin.y == ray.direction.y)
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
				a = (float)delta.y / (float)delta.x;
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
				a = (float)delta.y / (float)delta.x;
				b = ray.origin.y - a * ray.origin.x;
				h_intersection->x = (h_intersection->y - b) / a;
			}
			if (!is_wall(game, *h_intersection))
				h_intersection->y += game->minimap_block_d;
			else
				break ;
		}
	}
	return (TRUE);
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
			a = (float)delta.y / (float)delta.x;
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
	return (TRUE);
}

int		get_distance(t_pos p1, t_pos p2)
{
	int		d;

	d = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
	return (d);
}

void	cast_ray(t_vector ray, t_game *game, int angle)
{
	t_pos	h_intersection;
	t_pos	v_intersection;
	int		h_code;
	int		v_code;

	h_code = get_h_intersection(game, &h_intersection, ray);
	v_code = get_v_intersection(game, &v_intersection, ray);
	// if (v_code && v_intersection.x > 0 && v_intersection.x < SCREEN_WIDTH)
	// 	draw_line(new_vector(ray.origin, v_intersection), 0xA020F0);
	if (!h_code && v_code)
	{
		if (v_intersection.x > 0 && v_intersection.x < SCREEN_WIDTH)
			draw_line(new_vector(ray.origin, v_intersection), 0xA020F0);
	}
	else if (!v_code && h_code)
	{
		if (h_intersection.y > 0 && h_intersection.y < SCREEN_HEIGHT)
			draw_line(new_vector(ray.origin, h_intersection), 0xA020F0);
	}
	else
	{
		if (get_distance(ray.origin, v_intersection) < get_distance(ray.origin, h_intersection))
		{
			if (v_intersection.x > 0 && v_intersection.x < SCREEN_WIDTH)
				draw_line(new_vector(ray.origin, v_intersection), 0xA020F0);
		}
		else
		{
			if (h_intersection.y > 0 && h_intersection.y < SCREEN_HEIGHT)
				draw_line(new_vector(ray.origin, h_intersection), 0xA020F0);
		}
	}
}

int	render(t_game *game)
{
	int		angle;
	int		max_angle;
	int		x1;
	int		y1;
	int		i;

	clear();
	update_player_vector(game);
	draw_blocks(game, game->minimap_block_d);
	draw_player(*game, game->minimap_player_d);

	i = 0;
	angle = game->player_view_angle - VIEW_RANGE / 2;
	while (i < VIEW_RANGE)
	{
		if (angle >= 360)
			angle = angle - 360;
		x1 = round(DIRECTION_LEN * cos((angle) * PI / 180));
		y1 = round(DIRECTION_LEN * sin((angle) * PI / 180));
		// draw_line(new_vector(game->player_vector.origin, new_pos(game->player_vector.direction.x + x1, game->player_vector.direction.y + y1)), 0xA020F0);
		cast_ray(new_vector(game->player_vector.origin, new_pos(game->player_vector.direction.x + x1, game->player_vector.direction.y + y1)), game, angle);
		angle++;
		i++;
	}
	cast_ray(game->player_vector, game, game->player_view_angle);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

// block_d = 100;
// y = 233
// new_y = y / block_d * block_d

int	main(void)
{
	t_game	game;

	/* parsing */
	game.map_height = 8; // 8, 4
	game.map_width = 6; // 6, 22
	game.player_vector.origin.x = 4; // player x position
	game.player_vector.origin.y = 4; // player y position
	game.player_orientation = NORTH; // looking left
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
// 	game.map = "\
// 1111111111111111111111\
// 1000000000000000000001\
// 1000000000000000000001\
// 1111111111111111111111";
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
