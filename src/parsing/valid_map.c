/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:09:55 by fberthou          #+#    #+#             */
/*   Updated: 2024/11/15 10:33:42 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

static int	valid_char(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	check_condition(char **map, size_t x, size_t y, size_t heigth)
{
	static size_t	line_len;

	if (!line_len)
		line_len = ft_strlen(map[0]);
	return (((y == 0 || y == heigth - 1) && valid_char(map[y][x])) || \
			(y > 0 && valid_char(map[y - 1][x])) || \
			(x > 0 && valid_char(map[y][x - 1])) || \
			(y < heigth - 1 && valid_char(map[y + 1][x])) || \
			(x < line_len && valid_char(map[y][x + 1])));
}

int	check_map_validity(t_game *game)
{
	static size_t	x;
	static size_t	y;

	while (game->map_data.map[y])
	{
		while (game->map_data.map[y][x])
		{
			if (game->map_data.map[y][x] == ' ' || \
				game->map_data.map[y][x] == '\t')
			{
				if (check_condition(game->map_data.map, x, y, \
									game->map_data.heigth))
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
