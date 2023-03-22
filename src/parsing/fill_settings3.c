/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_settings3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:55:39 by yabidi            #+#    #+#             */
/*   Updated: 2023/03/21 20:59:30 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
