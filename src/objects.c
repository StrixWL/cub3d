/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 21:16:08 by bel-amri          #+#    #+#             */
/*   Updated: 2023/03/17 04:33:52 by bel-amri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.h>

t_pos	new_pos(float x, float y)
{
	t_pos	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

t_vector	new_vector(t_pos origin, t_pos direction)
{
	t_vector	vector;

	vector.origin = origin;
	vector.direction = direction;
	return (vector);
}
