/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:23:23 by yabidi            #+#    #+#             */
/*   Updated: 2023/03/20 14:30:58 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.h>

char	*conv_hex(int number, char *hexadecimal)
{
	char	*keep;
	char	*my_num;
	char	*ret;

	my_num = malloc(sizeof(char) + 1);
	my_num[1] = '\0';
	if (number >= 16)
		keep = conv_hex((number / 16), hexadecimal);
	else
		keep = ft_strdup("");
	*my_num = hexadecimal[number % 16];
	ret = ft_strjoin(keep, my_num);
	free(keep);
	free(my_num);
	return (ret);
}

int	conv_int2(char *hex, int res, int len, int i)
{
	if (hex[i] == 'F')
			res += 15 * pow(16, (len - i));
	else if (hex[i] == 'E')
		res += 14 * pow(16, (len - i));
	else if (hex[i] == 'D')
		res += 13 * pow(16, (len - i));
	else if (hex[i] == 'C')
		res += 12 * pow(16, (len - i));
	else if (hex[i] == 'B')
		res += 11 * pow(16, (len - i));
	else if (hex[i] == 'A')
		res += 10 * pow(16, (len - i));
	else
		res += (hex[i] - 48) * pow(16, (len - i));
	return (res);
}

int	conv_int(char *hex)
{
	int	len;
	int	i;
	int	res;

	i = 0;
	len = ft_strlen(hex) - 1;
	res = 0;
	while (i <= len)
	{
		res = conv_int2(hex, res, len, i);
		i++;
	}
	return (res);
}

int	take_floor_color(t_game *game, char *s)
{
	char	**rgb;
	char	*keep;
	char	*keep2;
	char	*hex;
	int		i;

	i = 0;
	rgb = ft_split(s, ',');
	hex = ft_strdup("");
	while (rgb[i])
	{
		keep = hex;
		keep2 = conv_hex(ft_atoi(*(rgb + i)), "0123456789ABCDEF");
		hex = ft_strjoin(hex, keep2);
		free(keep);
		free(keep2);
		free(rgb[i]);
		i++;
	}
	free(rgb);
	game->floor_color = conv_int(hex);
	return (0);
}

int	take_ciel_color(t_game *game, char *s)
{
	char	**rgb;
	char	*keep;
	char	*keep2;
	char	*hex;
	int		i;

	rgb = ft_split(s, ',');
	hex = ft_strdup("");
	i = 0;
	while (rgb[i])
	{
		keep = hex;
		keep2 = conv_hex(ft_atoi(*(rgb + i)), "0123456789ABCDEF");
		hex = ft_strjoin(hex, keep2);
		free(keep);
		free(keep2);
		free(rgb[i]);
		i++;
	}
	free(rgb);
	game->ciel_color = conv_int(hex);
	return (0);
}
