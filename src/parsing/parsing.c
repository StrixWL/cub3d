/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 02:28:29 by yabidi            #+#    #+#             */
/*   Updated: 2023/03/20 15:17:12 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	open_file(char *s)
{
	int	fd;

	if (!s)
		return (-1);
	if (ft_strcmp((s + (ft_strlen(s) - 4)), ".cub"))
		return (-1);
	fd = open(s, O_RDONLY);
	if (!fd)
		return (-1);
	return (fd);
}

void	free_file(t_file *file)
{
	t_file	*temp;

	temp = file;
	while (file)
	{
		temp = file->next;
		free(file->line);
		free(file);
		file = temp;
	}
}

void	free_settings(t_settings *settings)
{
	t_settings	*temp;

	temp = settings;
	while (settings)
	{
		temp = settings->next;
		free(settings->value);
		free(settings);
		settings = temp;
	}
}

void	skip_spaces(char **s)
{
	while (**s == ' ' || **s == '\t')
			(*s)++;
}

int	parsing(char *s, t_settings *settings)
{
	int		fd;
	t_file	*file;

	fd = open_file(s);
	if (fd == -1)
		return (write(2, "Error\nfile error", 16), -1);
	file = new_node_file();
	if (!file)
		return (-1);
	if (fill_file(fd, file))
		return (free_file(file), -1);
	if (check_all(file) == -1)
		return (free_file(file), -1);
	if (fill_settings(settings, file))
		return (free_file(file), free_settings(settings), -1);
	return (free_file(file), 0);
}
