/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_all4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:09:33 by yabidi            #+#    #+#             */
/*   Updated: 2023/03/20 15:16:55 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_inside_map(t_file *file, char *s1)
{
	char	*s2;
	char	*s;
	int		player;
	char	*keep_line;

	s = ft_strdup(s1);
	keep_line = NULL;
	player = 0;
	s2 = (file->next)->line;
	while (file->next)
	{
		free(keep_line);
		keep_line = ft_strdup(file->line);
		if (check_line(file, s, s2, &player) == -1)
			return (free(s), free(keep_line), -1);
		free(s);
		s = ft_strdup(keep_line);
		file = file->next;
		if (file->next)
			s2 = (file->next)->line;
	}
	return (is_multiplayer(keep_line, s, player));
}

int	check_border(t_file *file)
{
	int	i;

	i = 0;
	while ((file->line)[i])
	{
		if ((file->line)[i] != '1' && (file->line)[i] != ' '
			&& (file->line)[i] != '\t' && (file->line)[i] != '\n')
		{
			write(2, "Error\nopen border", 17);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	check_map_and_nelements_array(t_file *file, char *check_elem, char *s)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (check_elem[i] == '0')
		{
			write(2, "Error\nIncomplete texture elements", 33);
			return (-1);
		}
		i++;
	}
	if (!file->next || !(file->next)->next)
		return (write(2, "Error\nmap too small", 19), -1);
	if (check_border(file) == -1)
		return (-1);
	file = file->next;
	if (check_inside_map(file, s) == -1)
		return (-1);
	while (file->next && *(file->next)->line != '\n')
		file = file->next;
	if (check_border(file) == -1)
		return (-1);
	return (0);
}

int	is_line_empty(char *s)
{
	while (*s)
	{
		if ((*s != '\t' && *s != ' ' && *s != '\n'))
			return (0);
		s++;
	}
	return (1);
}

void	free_empty_lines(t_file *file)
{
	t_file	*temp;
	t_file	*temp2;

	while (file && !is_line_empty(file->line))
	{
		temp2 = file;
		file = file->next;
	}
	if (!file)
		return ;
	temp = file;
	while (temp)
	{
		if (!is_line_empty(temp->line))
			return ;
		temp = temp->next;
	}
	while (file)
	{
		temp = file->next;
		free(file->line);
		free(file);
		file = temp;
	}
	temp2->next = NULL;
}
