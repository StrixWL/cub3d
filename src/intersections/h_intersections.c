/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_intersections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:27:43 by bel-amri          #+#    #+#             */
/*   Updated: 2023/03/21 08:47:32 by bel-amri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_bool	is_wall(t_game *game, t_pos cord)
{
	int		wall_x;
	int		wall_y;

	wall_x = cord.x / BLOCK_D;
	wall_y = cord.y / BLOCK_D;
	if (wall_x + wall_y * game->map_width > game->map_len
		|| wall_x + wall_y * game->map_width < 0)
		return (FALSE);
	if (game->map[(wall_x + wall_y * game->map_width)] == '1')
		return (TRUE);
	return (FALSE);
}

void	looking_up_handler(t_game *game, t_pos *h_intersection,
					t_vector ray, t_ray_data *data)
{
	float	a;
	float	b;
	t_pos	delta;
	int		range;

	delta.x = ray.origin.x - ray.direction.x;
	delta.y = ray.origin.y - ray.direction.y;
	a = delta.y / delta.x;
	b = ray.origin.y - a * ray.origin.x;
	data->h_orientation = NORTH;
	h_intersection->y = floor(ray.origin.y / BLOCK_D)
		* BLOCK_D;
	range = h_intersection->y - RENDER_RANGE - 10000;
	h_intersection->x = ray.origin.x;
	while (h_intersection->y > range)
	{
		if (delta.x)
			h_intersection->x = (h_intersection->y - b) / a;
		if (!is_wall(game, new_pos(h_intersection->x,
					h_intersection->y - BLOCK_D)))
			h_intersection->y -= BLOCK_D;
		else
			break ;
	}
}

void	looking_down_handler(t_game *game, t_pos *h_intersection,
					t_vector ray, t_ray_data *data)
{
	float	a;
	float	b;
	t_pos	delta;
	int		range;

	delta.x = ray.origin.x - ray.direction.x;
	delta.y = ray.origin.y - ray.direction.y;
	a = delta.y / delta.x;
	b = ray.origin.y - a * ray.origin.x;
	data->h_orientation = SOUTH;
	h_intersection->y = (floor(ray.origin.y / BLOCK_D)
			* BLOCK_D) + BLOCK_D;
	range = h_intersection->y + RENDER_RANGE + 10000;
	h_intersection->x = ray.origin.x;
	while (h_intersection->y < range)
	{
		if (delta.x)
			h_intersection->x = (h_intersection->y - b) / a;
		if (!is_wall(game, *h_intersection))
			h_intersection->y += BLOCK_D;
		else
			break ;
	}
}

void	get_h_intersection(t_game *game, t_pos *h_intersection,
					t_vector ray, t_ray_data *data)
{
	if (ray.origin.y > ray.direction.y)
		looking_up_handler(game, h_intersection, ray, data);
	else
		looking_down_handler(game, h_intersection, ray, data);
}
