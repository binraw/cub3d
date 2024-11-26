/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:09:55 by fberthou          #+#    #+#             */
/*   Updated: 2024/11/26 21:03:59 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

static int	valid_char(char c)
{
	return (c == ' ' || c == '\t');
}

static int	check_condition(t_game *game, size_t x, size_t y)
{
	static size_t	line_len;
	static size_t	heigth;
	static char		**map;

	if (!line_len)
	{
		map = game->map_data.map;
		heigth = game->map_data.heigth;
		line_len = ft_strlen(map[0]);
	}
	if (y == 0 || y == heigth - 1 || x == 0 || x == line_len - 1)
		return (1);
	if (valid_char(map[y - 1][x]) || valid_char(map[y + 1][x]) || \
		valid_char(map[y][x - 1]) || valid_char(map[y][x + 1]))
		return (1);
	return (0);
}

int	check_map_validity(t_game *game)
{
	static size_t	x;
	static size_t	y;

	while (game->map_data.map[y])
	{
		while (game->map_data.map[y][x])
		{
			if (game->map_data.map[y][x] == '0' || \
				is_player(game->map_data.map[y][x]))
			{
				if (check_condition(game, x, y))
				{
					ft_perror("Map is not close in a line ");
					printf("(at [%zu][%zu])\n", y, x);
					return (1);
				}
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}
