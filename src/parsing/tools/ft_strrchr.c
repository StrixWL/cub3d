/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 03:02:23 by yabidi            #+#    #+#             */
/*   Updated: 2023/03/20 14:55:14 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

char	*ft_strrchr(const char *str, int ch)
{
	char	*s;
	size_t	l;

	s = (char *)str;
	l = ft_strlen(s);
	while (*(s + l) != (unsigned char)ch)
	{
		if (l == 0)
			return (0);
		l--;
	}
	return (s + l);
}
