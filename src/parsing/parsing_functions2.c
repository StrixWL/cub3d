/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:22:51 by yabidi            #+#    #+#             */
/*   Updated: 2023/03/20 20:36:40 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.h>

void	fill_player_infos(t_game *game, char *map, int h, int w)
{
	game->player.origin.x = w;
	game->player.origin.y = h;
	if (*map == 'N')
		game->player_orientation = NORTH;
	else if (*map == 'S')
		game->player_orientation = SOUTH;
	else if (*map == 'E')
		game->player_orientation = EAST;
	else if (*map == 'W')
		game->player_orientation = WEST;
}

void	get_x_y_orientation(t_game *game, char *map, int width)
{
	int	h;
	int	w;

	h = 0;
	w = 0;
	while (*map)
	{
		if (*map == 'N' || *map == 'S' || *map == 'E' || *map == 'W')
		{
			fill_player_infos(game, map, h, w);
			return ;
		}
		if (w == width)
		{
			w = 0;
			h++;
		}
		w++;
		map++;
	}
}

int	take_w_h2(char *s, char **width, char **heigh, int i)
{
	while (*s >= '0' && *s <= '9')
		s++;
	while (*s == ' ' || *s == '\t')
		s++;
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	(*width) = malloc((i + 2) * sizeof(char));
	if (!(*width))
		return (free(*heigh), -1);
	(*width)[i + 2] = '\0';
	i = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		(*width)[i] = s[i];
		i++;
	}
	return (0);
}

int	take_w_h(char *s, int *w, int *h)
{
	char	*heigh;
	char	*width;
	int		i;

	i = 0;
	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	heigh = malloc((i + 2) * sizeof(char));
	if (!heigh)
		return (-1);
	heigh[i + 2] = '\0';
	i = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		heigh[i] = s[i];
		i++;
	}
	if (take_w_h2(s, &width, &heigh, i) == -1)
		return (-1);
	*w = ft_atoi(width);
	*h = ft_atoi(heigh);
	return (free(width), free(heigh), 0);
}

int	search_quotes(char *s)
{
	int	comment;
	int	quotes;

	quotes = 0;
	comment = 0;
	while (*s)
	{
		if ((*s) == '/' && *(s + 1) == '*')
			comment++;
		if ((*s) == '*' && *(s + 1) == '/' && comment)
			comment--;
		if (*s == '"' && !comment)
			quotes++;
		if (quotes == 2)
			return (1);
		s++;
	}
	return (0);
}

char	*read_picture(int fd)
{
	int		i;
	char	*s;
	char	*keep;
	char	*whole_pic;

	s = malloc(sizeof(char));
	i = 0;
	whole_pic = ft_strdup("");
	read(fd, s, 1);
	while (s)
	{
		keep = whole_pic;
		whole_pic = ft_strjoin(whole_pic, s);
		free(keep);
		if (search_quotes(whole_pic))
			break ;
		read(fd, s, 1);
	}
	free(s);
	return (whole_pic);
}
