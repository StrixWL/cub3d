/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_all2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:08:05 by yabidi            #+#    #+#             */
/*   Updated: 2023/03/20 15:17:27 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*ft_strdup2(char *src)
{
	size_t	i;
	size_t	len;
	char	*res;

	while (*src && (*src == ' ' || *src == '\t'))
		src++;
	while (*src && *src != ' ' && *src != '\t')
		src++;
	while (*src && (*src == ' ' || *src == '\t'))
		src++;
	res = 0;
	i = 0;
	len = ft_strlen(src);
	if (src[len - 1] == '\n')
		len--;
	res = malloc(sizeof(char) * len + 1);
	res[len] = '\0';
	if (res == NULL)
		return (0);
	while (i < len)
	{
		res[i] = src[i];
		i++;
	}
	return (res);
}

int	check_elems4(char *s, int i, char *check_elem)
{
	if (!ft_strncmp((s + i), "F", 1)
		&& (*(s + i + 1) == ' ' || *(s + i + 1) == '\t'))
	{
		if (check_elem[4] == '1')
			return (write(2, "Error\nDuplicated element", 24), -1);
		check_elem[4] = '1';
	}
	else if (!ft_strncmp((s + i), "C", 1)
		&& (*(s + i + 1) == ' ' || *(s + i + 1) == '\t'))
	{
		if (check_elem[5] == '1')
			return (write(2, "Error\nDuplicated element", 24), -1);
		check_elem[5] = '1';
	}
	else
		return (write(2, "Error\nNo such element", 21), -1);
	return (0);
}

int	check_elems3(char *s, int i, char *check_elem)
{
	if (!ft_strncmp((s + i), "WE", 2)
		&& (*(s + i + 2) == ' ' || *(s + i + 2) == '\t'))
	{
		if (check_elem[2] == '1')
			return (write(2, "Error\nDuplicated element", 24), -1);
		check_elem[2] = '1';
	}
	else if (!ft_strncmp((s + i), "EA", 2)
		&& (*(s + i + 2) == ' ' || *(s + i + 2) == '\t'))
	{
		if (check_elem[3] == '1')
			return (write(2, "Error\nDuplicated element", 24), -1);
		check_elem[3] = '1';
	}
	else
		return (check_elems4(s, i, check_elem));
	return (0);
}

int	check_elements2(char *s, int i, char *check_elem)
{
	if (!ft_strncmp((s + i), "NO", 2)
		&& (*(s + i + 2) == ' ' || *(s + i + 2) == '\t'))
	{
		if (check_elem[0] == '1')
			return (write(2, "Error\nDuplicated element", 24), -1);
		check_elem[0] = '1';
	}
	else if (!ft_strncmp((s + i), "SO", 2)
		&& (*(s + i + 2) == ' ' || *(s + i + 2) == '\t'))
	{
		if (check_elem[1] == '1')
			return (write(2, "Error\nDuplicated element", 24), -1);
		check_elem[1] = '1';
	}
	else
		return (check_elems3(s, i, check_elem));
	return (0);
}

int	check_elements(char *s, char *check_elem)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] == '\t' || s[i] == ' ' || s[i] == '\n'))
			i++;
	if (check_elements2(s, i, check_elem) == -1)
		return (-1);
	while (s[i] && s[i] != ' ' && s[i] != '\t')
		i++;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	if (!s[i] || s[i] == '\n')
		return (write(1, "Error\nNO texture or colour", 26), -1);
	return (0);
}
