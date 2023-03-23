/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 21:27:42 by bel-amri          #+#    #+#             */
/*   Updated: 2023/03/22 21:59:58 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
	if (keycode == 53)
		exit(0);
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

void	display_pressed_buttons(t_game *game)
{
	if (game->pressed_keys.m_forward)
		mlx_string_put(game->mlx, game->win, 600, 200, 0xA020F0, "w");
	if (game->pressed_keys.m_backward)
		mlx_string_put(game->mlx, game->win, 600, 230, 0xA020F0, "z");
	if (game->pressed_keys.m_right)
		mlx_string_put(game->mlx, game->win, 630, 230, 0xA020F0, "d");
	if (game->pressed_keys.m_left)
		mlx_string_put(game->mlx, game->win, 570, 230, 0xA020F0, "a");
	if (game->pressed_keys.r_right)
		mlx_string_put(game->mlx, game->win, 630, 250, 0xA020F0, "right");
	if (game->pressed_keys.r_left)
		mlx_string_put(game->mlx, game->win, 540, 250, 0xA020F0, "left");
}
