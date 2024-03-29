/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 10:57:19 by yabidi            #+#    #+#             */
/*   Updated: 2023/03/24 12:07:39 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.h>

int	search_quotes(char *s)
{
	int	comment;
	int	quotes;

	quotes = 0;
	comment = 0;
	while (*s)
	{
		if ((*s) == '/' && *(s + 1) == '*')
			comment = 1;
		if ((*s) == '*' && *(s + 1) == '/' && comment)
			comment = 0;
		if (*s == '"' && !comment)
			quotes++;
		if (quotes == 2)
			return (1);
		s++;
	}
	return (0);
}

int	get_w_h(int *w, int *h, int fd)
{
	char		*whole_pic;
	int			check;
	int			i;

	i = 0;
	check = 0;
	whole_pic = read_picture(fd);
	if (!whole_pic)
		return (-1);
	while (whole_pic[i])
	{
		if (whole_pic[i] == '/' && whole_pic[i + 1] == '*')
			check++;
		else if (check && (whole_pic[i] == '*' && whole_pic[i + 1] == '/'))
			check--;
		if (!check && (whole_pic[i] == '"'))
		{
			if (take_w_h((whole_pic + i + 1), w, h) == -1)
				return (-1);
			return (free(whole_pic), 0);
		}
		i++;
	}
	return (free((whole_pic)), -1);
}

int	fill_img_data(t_game *game, char *s, t_img_data *img)
{
	int	fd;
	int	w;
	int	h;
	int	check;

	fd = open(s, O_RDONLY);
	if (fd == -1)
		return (write(2, "Error\ncouldn't open texture file", 32), -1);
	check = get_w_h(&h, &w, fd);
	if (check == -1)
	{
		write(2, "Error\ncouldn't get height and width", 35);
		return (-1);
	}
	img->h = h;
	img->w = w;
	img->img = mlx_xpm_file_to_image(game->mlx, s, &w, &h);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	close(fd);
	return (0);
}

int	fill_imgs_data(t_game *game)
{
	int	i;
	int	check;

	i = 0;
	while (i < 6)
	{
		if (!ft_strncmp(game->settings->identifier, "NO", 2))
			check = fill_img_data(game, game->settings->value, &game->img_no);
		else if (!ft_strncmp(game->settings->identifier, "SO", 2))
			check = fill_img_data(game, game->settings->value, &game->img_so);
		else if (!ft_strncmp(game->settings->identifier, "EA", 2))
			check = fill_img_data(game, game->settings->value, &game->img_ea);
		else if (!ft_strncmp(game->settings->identifier, "WE", 2))
			check = fill_img_data(game, game->settings->value, &game->img_we);
		else if (!ft_strncmp(game->settings->identifier, "F", 1))
			check = take_floor_color(game, game->settings->value);
		else if (!ft_strncmp(game->settings->identifier, "C", 1))
			check = take_ciel_color(game, game->settings->value);
		if (check == -1)
			return (-1);
		game->settings = game->settings->next;
		i++;
	}
	return (0);
}
