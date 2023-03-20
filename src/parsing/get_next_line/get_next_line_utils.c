/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 01:43:41 by yabidi            #+#    #+#             */
/*   Updated: 2023/03/08 09:12:11 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*p;

	i = 0;
	p = malloc(count * size);
	if (!p)
		return (NULL);
	while (i < count * size)
	{
		((char *)p)[i] = 0;
		i++;
	}
	return (p);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*n;

	if (s1 == NULL || s2 == NULL)
		return (0);
	i = 0;
	n = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (n == NULL)
		return (0);
	while (*s1)
	{
		n[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		n[i] = *s2;
		s2++;
		i++;
	}
	n[i] = '\0';
	return (n);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	slen;
	char	*b;

	slen = len;
	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		slen = ft_strlen(s + start);
	b = ft_calloc(slen + 1, sizeof(char));
	if (!b)
		return (NULL);
	while (i < len && s[start + i])
	{
		b[i] = s[start + i];
		i++;
	}
	return (b);
}

char	*ft_strdup(char *src)
{
	size_t	i;
	size_t	len;
	char	*res;

	res = 0;
	i = 0;
	len = ft_strlen(src);
	res = malloc(sizeof(char) * len + 1);
	if (res == NULL)
		return (0);
	while (i <= len)
	{
		res[i] = src[i];
		i++;
	}
	return (res);
}
