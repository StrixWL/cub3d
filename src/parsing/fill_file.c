/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 17:36:59 by yabidi            #+#    #+#             */
/*   Updated: 2023/03/20 20:28:18 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_file	*new_node_file(void)
{
	t_file	*ret;

	ret = malloc(sizeof(t_file));
	if (!ret)
		return (NULL);
	ret->next = NULL;
	return (ret);
}

int	fill_file(int fd, t_file *file)
{
	char	*s;
	t_file	*keep;

	s = get_next_line(fd);
	if (!s)
	{
		close(fd);
		exit(1);
	}
	while (s)
	{
		keep = file;
		file->line = s;
		file->next = new_node_file();
		file = file->next;
		if (!file)
			return (-1);
		s = get_next_line(fd);
	}
	free(file);
	keep->next = NULL;
	return (0);
}
