/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 17:38:22 by yabidi            #+#    #+#             */
/*   Updated: 2023/03/20 17:22:54 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_first_line(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (s[i] == '1' || s[i] == '0')
		return (1);
	return (0);
}

char	*skip_spaces_and_emptylines(t_file **file)
{
	int	i;

	while (*file)
	{
		i = 0;
		while ((*file)->line[i] == '\t'
			|| (*file)->line[i] == ' ' || (*file)->line[i] == '\n')
			i++;
		if ((*file)->line[i])
			return ((*file)->line);
		if (!(*file)->line[i])
			(*file) = (*file)->next;
	}
	return (NULL);
}

int	check_all(t_file *file)
{
	int		i;
	char	check_elem[6];
	char	*s;

	i = 0;
	while (i < 6)
	{
		check_elem[i] = '0';
		i++;
	}
	while (file)
	{
		s = skip_spaces_and_emptylines(&file);
		if (!s)
			break ;
		if (is_first_line(s))
			return (free_empty_lines(file),
				check_map_and_nelements_array(file, check_elem, s));
		else if (check_elements(s, check_elem) != -1)
			file = file->next;
		else
			return (-1);
	}
	return (write(2, "Error\nIncomplete map file", 25), -1);
}
