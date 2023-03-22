/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_parsing_infos.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:13:19 by yabidi            #+#    #+#             */
/*   Updated: 2023/03/21 20:23:57 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	take_parsing_infos(t_game *game, t_settings *settings)
{
	t_settings	*temp;

	temp = settings;
	while (temp->next)
		temp = temp->next;
	game->map = temp->value;
	game->map_height = ft_strlen(temp->value) / temp->size;
	game->map_width = temp->size;
	get_x_y_orientation(game, temp->value, temp->size);
	game->map_len = ft_strlen(game->map);
	game->settings = settings;
}
