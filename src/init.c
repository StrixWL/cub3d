/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 04:49:07 by bel-amri          #+#    #+#             */
/*   Updated: 2023/03/21 20:00:28 by bel-amri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_img_data	*img_save(t_img_data *data)
{
	static t_img_data	*saved_data;

	if (!saved_data)
		saved_data = data;
	return (saved_data);
}

void	init_keys(t_game *game)
{
	game->pressed_keys.r_right = FALSE;
	game->pressed_keys.r_left = FALSE;
	game->pressed_keys.m_right = FALSE;
	game->pressed_keys.m_left = FALSE;
	game->pressed_keys.m_forward = FALSE;
	game->pressed_keys.m_backward = FALSE;
}

void	set_player_data(t_game *game)
{
	game->player.origin.x = game->player.origin.x * BLOCK_D + BLOCK_D / 2;
	game->player.origin.y = game->player.origin.y * BLOCK_D + BLOCK_D / 2;
	game->player.direction.x = game->player.origin.x;
	game->player.direction.y = game->player.origin.y;
	if (game->player_orientation == NORTH)
		game->player.direction.y -= DIRECTION_LEN;
	else if (game->player_orientation == SOUTH)
		game->player.direction.y += DIRECTION_LEN;
	else if (game->player_orientation == EAST)
		game->player.direction.x += DIRECTION_LEN;
	else if (game->player_orientation == WEST)
		game->player.direction.x -= DIRECTION_LEN;
	if (game->player_orientation == NORTH)
		game->player_view_angle = 270;
	else if (game->player_orientation == SOUTH)
		game->player_view_angle = 90;
	else if (game->player_orientation == EAST)
		game->player_view_angle = 0;
	else if (game->player_orientation == WEST)
		game->player_view_angle = 180;
	init_keys(game);
}
