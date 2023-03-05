/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 01:01:37 by bel-amri          #+#    #+#             */
/*   Updated: 2023/03/05 01:44:34 by bel-amri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.h>

void	draw_blocks(t_game *game, int d)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	while (game->map[i])
	{
		x = (i % game->map_width) * d;
		y = (i / game->map_width) * d;
		if (game->map[i] == '1')
			draw_square(x, y, d, 0xFF0000);
		if (game->map[i++] == 'P')
			game->player_pos = new_pos(x, y);
	}
}

void	draw_player(t_game game, int d)
{
	draw_square((game.player_pos.x + game.minimap_block_d / 2) - game.minimap_player_d / 2, (game.player_pos.y + game.minimap_block_d / 2) - game.minimap_player_d / 2, d, 0x0000FF);
}
