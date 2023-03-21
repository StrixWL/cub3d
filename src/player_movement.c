/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 04:41:25 by bel-amri          #+#    #+#             */
/*   Updated: 2023/03/21 18:38:59 by bel-amri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	handle_rotation(t_game *game)
{
	if (game->pressed_keys.r_left)
	{
		game->player_view_angle -= ROT_SPEED;
		if (game->player_view_angle < 0)
			game->player_view_angle = 360 - abs(game->player_view_angle);
	}
	if (game->pressed_keys.r_right)
	{
		game->player_view_angle += ROT_SPEED;
		if (game->player_view_angle >= 360)
			game->player_view_angle = game->player_view_angle - 360;
	}
}

static t_bool	is_wall(t_game *game, t_pos cord)
{
	int		wall_x;
	int		wall_y;

	cord.x += game->player.origin.x;
	cord.y += game->player.origin.y;
	wall_x = cord.x / BLOCK_D;
	wall_y = cord.y / BLOCK_D;
	if (wall_x + wall_y * game->map_width > game->map_len
		|| wall_x + wall_y * game->map_width < 0)
		return (FALSE);
	if (game->map[(wall_x + wall_y * game->map_width)] == '1')
		return (TRUE);
	return (FALSE);
}

static void	handle_forward_backward(t_game *game, float x1, float y1)
{
	x1 = MVT_SPEED * sin((90 - game->player_view_angle) * PI / 180);
	y1 = MVT_SPEED * cos((90 - game->player_view_angle) * PI / 180);
	if (game->pressed_keys.m_forward)
	{
		if (!is_wall(game, new_pos(0, y1)))
			game->player.origin.y += y1;
		if (!is_wall(game, new_pos(x1, 0)))
			game->player.origin.x += x1;
	}
	if (game->pressed_keys.m_backward)
	{
		if (!is_wall(game, new_pos(-x1, 0)))
			game->player.origin.x -= x1;
		if (!is_wall(game, new_pos(0, -y1)))
			game->player.origin.y -= y1;
	}
}

static void	handle_left_right(t_game *game, float x1, float y1)
{
	x1 = MVT_SPEED * cos((90 - game->player_view_angle) * PI / 180);
	y1 = MVT_SPEED * sin((90 - game->player_view_angle) * PI / 180);
	if (game->pressed_keys.m_left)
	{
		if (!is_wall(game, new_pos(x1, 0)))
			game->player.origin.x += x1;
		if (!is_wall(game, new_pos(0, -y1)))
			game->player.origin.y -= y1;
	}
	if (game->pressed_keys.m_right)
	{
		if (!is_wall(game, new_pos(-x1, 0)))
			game->player.origin.x -= x1;
		if (!is_wall(game, new_pos(0, y1)))
			game->player.origin.y += y1;
	}
}

void	update_player(t_game *game)
{
	if (game->pressed_keys.r_left || game->pressed_keys.r_right)
		handle_rotation(game);
	if (game->pressed_keys.m_forward || game->pressed_keys.m_backward)
		handle_forward_backward(game, 0, 0);
	if (game->pressed_keys.m_left || game->pressed_keys.m_right)
		handle_left_right(game, 0, 0);
	game->player.direction.x = game->player.origin.x + DIRECTION_LEN;
	game->player.direction.y = game->player.origin.y + DIRECTION_LEN;
}
