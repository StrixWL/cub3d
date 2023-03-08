t_bool	get_v_intersection(t_game *game, t_pos *h_intersection, int angle, t_vector ray)
{
	float	a;
	float	b;
	t_pos	delta;


	if (angle == 90 || angle == 270)
		return (FALSE);
	else if (angle > 90 && angle < 270) // looking left
	{
		h_intersection->x = floor(ray.origin.x / game->minimap_block_d) * game->minimap_block_d;
		while (h_intersection->x > 0)
		{
			delta.x = ray.origin.x - ray.direction.x;
			delta.y = ray.origin.y - ray.direction.y;
			if (!delta.x)
				h_intersection->x = ray.origin.x;
			else
			{
				a = (float)delta.y / (float)delta.x;
				b = ray.origin.y - a * ray.origin.x;
				h_intersection->y = a * h_intersection->x + b;
			}
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
			if (!delta.x)
				h_intersection->x = ray.origin.x;
			else
			{
				a = (float)delta.y / (float)delta.x;
				b = ray.origin.y - a * ray.origin.x;
				h_intersection->y = a * h_intersection->x + b;
			}
			if (!is_wall(game, *h_intersection))
				h_intersection->x += game->minimap_block_d;
			else
				break ;
		}
	}
	return (TRUE);
}