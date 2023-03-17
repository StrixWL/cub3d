/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 00:09:01 by bel-amri          #+#    #+#             */
/*   Updated: 2023/03/17 21:38:40 by bel-amri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

float	get_distance(t_pos p1, t_pos p2)
{
	float		d;

	d = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
	return (d);
}

t_ray_data	cast_ray(t_vector ray, t_game *game, int color)
{
	t_pos		h_intersection;
	t_pos		v_intersection;
	t_ray_data	data[2];

	get_h_intersection(game, &h_intersection, ray, &data[0]);
	get_v_intersection(game, &v_intersection, ray, &data[1]);
	data[0].distance = get_distance(ray.origin, h_intersection);
	data[1].distance = get_distance(ray.origin, v_intersection);
	data[0].intersection = h_intersection.x - floor(h_intersection.x
			/ game->minimap_block_d) * game->minimap_block_d;
	data[0].orientation = data[0].h_orientation;
	data[1].intersection = v_intersection.y - floor(v_intersection.y
			/ game->minimap_block_d) * game->minimap_block_d;
	data[1].orientation = data[1].v_orientation;
	if (data[1].distance < data[0].distance)
		return (data[1]);
	return (data[0]);
}
