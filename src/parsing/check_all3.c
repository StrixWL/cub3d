/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_all3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:09:08 by yabidi            #+#    #+#             */
/*   Updated: 2023/03/23 22:14:54 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_last_charachter_1(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	i--;
	while (i >= 0)
	{
		if (s[i] == '1')
			return (0);
		if (s[i] != '\n' && s[i] != ' ' && s[i] != '\t')
			return (-1);
		i--;
	}
	return (0);
}

int	known_charachters(t_file *file, int i)
{
	if ((file->line)[i] != '1'
			&& (file->line)[i] != '0' && (file->line)[i] != 'N'
		&& (file->line)[i] != 'S' && (file->line)[i] != 'E'
		&& (file->line)[i] != 'W' && (file->line)[i] != ' '
		&& (file->line)[i] != '\t' && (file->line)[i] != '\n')
		return (-1);
	return (0);
}

int	check_line2(t_file *file, char *s, char *s2, int *player)
{
	int	i;

	i = 1;
	while ((file->line)[i])
	{
		if ((file->line)[i] == 'N' || (file->line)[i] == 'S'
				|| (file->line)[i] == 'E' || (file->line)[i] == 'W')
			(*player)++;
		if (known_charachters(file, i) == -1)
		{
			write(2, "Error\nstrange character detected", 32);
			return (-1);
		}
		if (((file->line)[i] != '1' && (file->line)[i] != '\n'
			&& (file->line)[i] != ' ' && (file->line)[i] != '\t')
				&& (((file->line)[i - 1] == ' ' || (file->line)[i - 1] == '\t')
				|| ((file->line)[i + 1] == ' ' || (file->line)[i + 1] == '\t')
				|| ((int)ft_strlen(s) - 1 <= i || s[i] == ' ' || s[i] == '\t')
				|| ((int)ft_strlen(s2) - 1 <= i
				|| s2[i] == ' ' || s2[i] == '\t')))
			return (write(2, "Error\nopen map", 14), -1);
		i++;
	}
	return (0);
}

int	check_line(t_file *file, char *s, char *s2, int *player)
{
	int	j;

	j = 0;
	while ((file->line)[j] == '\t' || (file->line)[j] == ' ')
			j++;
	if ((file->line)[j] == '\n' || !(file->line)[j])
	{
		write(2, "Error\nEmpty line in the map", 27);
		return (-1);
	}
	if ((file->line)[j] != '1')
	{
		write(2, "Error\nopen border", 17);
		return (-1);
	}
	if (is_last_charachter_1(file->line))
	{
		write(2, "Error\nopen border", 17);
		return (-1);
	}
	return (check_line2(file, s, s2, player));
}

int	is_multiplayer(char *keep_line, char *s, int player)
{
	free(keep_line);
	free(s);
	if (player > 1)
		return (write(2, "Error\ncannot have more than one player", 38), -1);
	if (player == 0)
		return (write(2, "Error\nno player in the map", 26), -1);
	return (0);
}
