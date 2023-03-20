/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_settings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 17:42:51 by yabidi            #+#    #+#             */
/*   Updated: 2023/03/20 18:00:05 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_color2(char *s, int *j, int *i)
{
	if (*i > 2)
		return (write(2, "Error\ncolor isn't valid", 23), -1);
	if (!(s[*j] >= '0' && s[*j] <= '9'))
		return (write(2, "Error\ncolor isn't valid", 23), -1);
	(*i)++;
	(*j)++;
	return (0);
}

int	check_color(char *str)
{
	int		check;
	char	*s;
	int		i;
	int		j;

	j = 0;
	check = 0;
	s = remove_spaces(str);
	if (!s)
		return (-1);
	while (check++ < 3)
	{
		i = 0;
		while (s[j] && s[j] != ',')
			if (check_color2(s, &j, &i) == -1)
				return (-1);
		if (s[j] != ',' && (check) != 3)
			return (write(2, "Error\ncolor isn't valid", 23), -1);
		if (s[j])
			j++;
	}
	if (s[j] && (s[j] != ' ' || s[j] != '\t' || s[j] != '\n'))
		return (write(2, "Error\ncolor isn't valid", 23), -1);
	return (free(s), 0);
}

void	remove_new_lines(t_file *file)
{
	int	i;

	while (file)
	{
		i = 0;
		while (file->line[i])
		{
			if (file->line[i] == '\n')
				file->line[i] = '\0';
			i++;
		}
		file = file->next;
	}
}

int	is_elem2(t_settings *settings, t_file *file)
{
	if (!ft_strncmp2(file->line, "WE", 2))
	{
		settings->identifier = "WE";
		settings->value = ft_strdup2((file->line));
	}
	else if (!ft_strncmp2(file->line, "EA", 2))
	{
		settings->identifier = "EA";
		settings->value = ft_strdup2((file->line));
	}
	else if (!ft_strncmp2(file->line, "SO", 2))
	{
		settings->identifier = "SO";
		settings->value = ft_strdup2((file->line));
	}
	else
		return (1);
	return (0);
}

int	is_elem(t_settings *settings, t_file *file)
{
	if (!ft_strncmp2(file->line, "NO", 2))
	{
		settings->identifier = "NO";
		settings->value = ft_strdup2((file->line));
	}
	else if (!ft_strncmp2(file->line, "C", 1))
	{
		settings->identifier = "C";
		settings->value = ft_strdup2((file->line));
		if (check_color(settings->value) == -1)
			return (-1);
	}
	else if (!ft_strncmp2(file->line, "F", 1))
	{
		settings->identifier = "F";
		settings->value = ft_strdup2((file->line));
		if (check_color(settings->value) == -1)
			return (-1);
	}
	else if (is_elem2(settings, file))
		return (1);
	return (0);
}

int	fill_settings(t_settings *settings, t_file *file)
{
	int	check;

	while (file)
	{
		skip_spaces_and_emptylines(&file);
		check = is_elem(settings, file);
		if (check == 1)
			break ;
		else if (check == -1)
			return (-1);
		settings->next = new_node_settings();
		settings = settings->next;
		if (!settings)
			return (-1);
		file = file->next;
	}
	remove_new_lines(file);
	return (fill_map(file, settings));
}
