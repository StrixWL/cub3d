/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_intersections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:27:43 by bel-amri          #+#    #+#             */
/*   Updated: 2023/03/20 13:17:21 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_bool	is_wall(t_game *game, t_pos cord)
{
	int		wall_x;
	int		wall_y;

	wall_x = cord.x / game->minimap_block_d;
	wall_y = cord.y / game->minimap_block_d;
	if (wall_x + wall_y * game->map_width > game->map_len
		| wall_x + wall_y * game->map_width < 0)
		return (FALSE);
	if (game->map[(wall_x + wall_y * game->map_width)] == '1')
		return (TRUE);
	return (FALSE);
}

void	looking_left_handler(t_game *game, t_pos *v_intersection,
				float a, float b)
{
	int		range;

	range = v_intersection->x - RENDER_RANGE - 1000;
	while (v_intersection->x > range)
	{
		v_intersection->y = a * v_intersection->x + b;
		if (!is_wall(game, new_pos(v_intersection->x - game->minimap_block_d,
					v_intersection->y)))
			v_intersection->x -= game->minimap_block_d;
		else
			break ;
	}
}

void	looking_right_handler(t_game *game, t_pos *v_intersection,
					float a, float b)
{
	int		range;

	range = v_intersection->x + RENDER_RANGE + 1000;
	while (v_intersection->x < range)
	{
		v_intersection->y = a * v_intersection->x + b;
		if (!is_wall(game, *v_intersection))
			v_intersection->x += game->minimap_block_d;
		else
			break ;
	}
}

void	get_v_intersection(t_game *game, t_pos *v_intersection,
						t_vector ray, t_ray_data *data)
{
	float	a;
	float	b;
	t_pos	delta;

	delta.x = ray.origin.x - ray.direction.x;
	delta.y = ray.origin.y - ray.direction.y;
	a = delta.y / delta.x;
	b = ray.origin.y - a * ray.origin.x;
	if (ray.origin.x > ray.direction.x)
	{
		data->v_orientation = WEST;
		v_intersection->x = floor(ray.origin.x / game->minimap_block_d)
			* game->minimap_block_d;
		looking_left_handler(game, v_intersection, a, b);
	}
	else
	{
		data->v_orientation = EAST;
		v_intersection->x = (floor(ray.origin.x / game->minimap_block_d)
				* game->minimap_block_d) + game->minimap_block_d;
		looking_right_handler(game, v_intersection, a, b);
	}
}
