/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:03:39 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/11/14 09:49:29 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

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
			return (1);
		x_start++;
	}
	return (0);
}
