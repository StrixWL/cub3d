/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_settings2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:13:27 by yabidi            #+#    #+#             */
/*   Updated: 2023/03/20 17:59:36 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*remove_spaces(char *s)
{
	char	*ret;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	j = 0;
	i = 0;
	while (s[i])
		i++;
	i--;
	while (s[i] == ' ' || s[i] == '\t')
		i--;
	i++;
	ret = malloc ((i + 2) * sizeof(char));
	if (!ret)
		exit (1);
	while (j < i)
	{
		ret[j] = s[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

t_settings	*new_node_settings(void)
{
	t_settings	*ret;

	ret = malloc(sizeof(t_settings));
	if (!ret)
		exit (-1);
	ret->next = NULL;
	return (ret);
}

int	fill_map2(int len, int heigh, t_file *file, t_settings *settings)
{
	char	*map;
	int		i;
	int		j;

	i = 0;
	map = malloc(len * sizeof(char));
	if (!map)
		return (-1);
	while (file)
	{
		j = 0;
		while (file->line[j])
		{
			map[i] = file->line[j];
			i++;
			j++;
		}
		file = file->next;
	}
	map[i] = '\0';
	settings->identifier = "map";
	settings->value = map;
	settings->size = len / heigh;
	return (0);
}

char	*long_line(char *s, int len)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc((len + 1) * sizeof(char));
	ret[len] = '\0';
	while (i < len)
	{
		if (i < (int)ft_strlen(s))
			ret[i] = s[i];
		else
			ret[i] = '0';
		i++;
	}
	free(s);
	i = 0;
	while (ret[i])
	{
		if (ret[i] == ' ' || ret[i] == '\t')
			ret[i] = '0';
		i++;
	}
	return (ret);
}

int	fill_map(t_file *file, t_settings *settings)
{
	t_file	*temp;
	int		len;
	int		heigh;

	heigh = 0;
	len = 0;
	temp = file;
	while (temp)
	{
		if ((int)ft_strlen(temp->line) > len)
			len = ft_strlen(temp->line);
		heigh++;
		temp = temp->next;
	}
	temp = file;
	while (temp)
	{
		temp->line = long_line(temp->line, len);
		temp = temp->next;
	}
	heigh++;
	len = (len * heigh) + 1;
	return (fill_map2(len, heigh, file, settings));
}
