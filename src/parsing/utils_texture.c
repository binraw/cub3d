/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:00:59 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/11/14 10:46:51 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

size_t	ft_strlen_texture(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0' && str[i] != '\n')
	{
		i++;
	}
	return (i);
}

int check_line_validity(char **map, size_t x_start, size_t x_end, size_t y)
{
	while (map[y][x_end] == ' ' || map[y][x_end] == '\t')
		x_end--;
	while (x_start <= x_end)
	{
		if (map[y][x_start] == ' ' || map[y][x_start] == '\t')
			return (check_value_around(map, x_start, y));
		x_start++;
	}
	return (0);
}

int check_value_around(char **map, size_t x, size_t y)
{
	size_t tmp;

	tmp = x;
	while (map[y][x])
	{
		if (map[y][x] != '1')
		{
			if (map[y][x] != ' ')
				return (1);
		}
		x--;
	}
	x = tmp;
	while (map[y][x])
	{
		if (map[y][x] != '1')
		{
			if (map[y][x] != ' ')
				return (1);
		}
		x++;
	}
	return (0);
}