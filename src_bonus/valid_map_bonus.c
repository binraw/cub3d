/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:09:55 by fberthou          #+#    #+#             */
/*   Updated: 2024/11/13 16:27:03 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static int	check_column_loop(char **map, size_t heigth, size_t *x, size_t *y)
{
	const size_t	width = ft_strlen(map[*y]);

	while (*y < heigth && map[*y][*x] == ' ')
	{
		if (*x != 0 && map[*y][*x - 1] == '0')
			return (1);
		if (*x < width && map[*y][*x + 1] == '0')
			return (1);
		(*y)++;
	}
	if (map[*y][*x] != '1')
		return (1);
	*y = heigth - 1;
	while (*y != 0 && map[*y][*x] == ' ')
	{
		if (*x > 0 && map[*y][*x - 1] == '0')
			return (1);
		if (*x < width && map[*y][*x + 1] == '0')
			return (1);
		(*y)--;
	}
	return (0);
}

static int	check_columns(char **map, size_t heigth)
{
	size_t	x;
	size_t	y;

	y = 0;
	x = 0;
	while (y < heigth && map[y][x])
	{
		if (check_column_loop(map, heigth, &x, &y))
		{
			ft_perror("Map is not close in a column ");
			printf("(around [%zu][%zu])\n", y, x);
			return (1);
		}
		if (map[y][x] != '1')
		{
			ft_perror("Map is not close in a column ");
			printf("(around [%zu][%zu])\n", y, x);
			return (1);
		}
		y = 0;
		x++;
	}
	return (0);
}

static int	check_line_loop(char **map, size_t heigth, size_t *x, size_t *y)
{
	while (map[*y][*x] == ' ')
	{
		if (*y > 0 && map[*y - 1][*x] == '0')
			return (1);
		if (map[*y + 1] && *y < heigth && map[*y + 1][*x] == '0')
			return (1);
		(*x)++;
	}
	if (map[*y][*x] != '1')
		return (1);
	*x = ft_strlen(map[*y]) - 1;
	while (*x != 0 && map[*y][*x] == ' ')
	{
		if (*y > 0 && map[*y - 1][*x] == '0')
			return (1);
		if (*y < heigth - 1 && map[*y + 1][*x] == '0')
			return (1);
		(*x)--;
	}
	return (0);
}

static int	check_lines(char **map, size_t heigth)
{
	size_t	x;
	size_t	y;

	y = 0;
	x = 0;
	while (map[y])
	{
		if (check_line_loop(map, heigth, &x, &y))
		{
			ft_perror("Map is not close in a line ");
			printf("(around [%zu][%zu])\n", y, x);
			return (1);
		}
		if (map[y][x] == '0')
		{
			ft_perror("Map is not close in a line ");
			printf("(around [%zu][%zu])\n", y, x);
			return (1);
		}
		x = 0;
		y++;
	}
	return (0);
}

int	check_map_validity(t_game *game)
{
	if (check_lines(game->map_data.map, game->map_data.heigth))
		return (1);
	if (check_columns(game->map_data.map, game->map_data.heigth))
		return (1);
	return (0);
}
