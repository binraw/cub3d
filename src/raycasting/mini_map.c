/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:00:37 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/11/12 08:00:38 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	print_case(game_s *game, bool is_floor, int start_x, int start_y)
{
	int	curr_color;
	int	pos_x;
	int	pos_y;

	pos_x = (int)(game->plyr_data.pos_x / TILE_S);
	pos_y = (int)(game->plyr_data.pos_y / TILE_S);
	if (is_floor && (start_x != pos_x || start_y != pos_y))
		curr_color = 20000;
	else if (is_floor && start_x == pos_x && start_y == pos_y)
		curr_color = 0;
	else
		curr_color = 850606;
	write_pixel_minimap(game, start_x, start_y, curr_color);
}

void	write_pixel_minimap(game_s *game, int start_x,
		int start_y, int curr_color)
{
	const int	cell_w = (WIN_W / 7) / game->map_data.width;
	const int	cell_h = (WIN_H / 7) / game->map_data.heigth;
	int			tmp_x_y[2];

	start_x *= cell_w;
	start_y *= cell_h;
	tmp_x_y[0] = start_x;
	tmp_x_y[1] = start_y;
	while (start_y < tmp_x_y[1] + cell_h)
	{
		while (start_x < tmp_x_y[0] + cell_w)
		{
			my_mlx_pixel_put(&game->img, start_x, start_y, curr_color);
			start_x += 1;
		}
		start_x = tmp_x_y[0];
		start_y++;
	}
}

void	print_minimap(game_s *game, ray_s *ray)
{
	size_t	y;
	size_t	x;

	y = 0;
	x = 0;
	while (game->map_data.map[y])
	{
		while (game->map_data.map[y][x])
		{
			if (game->map_data.map[y][x] != ' '
				&& game->map_data.map[y][x] != '1')
				print_case(game, 1, x, y);
			else if (game->map_data.map[y][x] == '1')
				print_case(game, 0, x, y);
			x++;
		}
		x = 0;
		y++;
	}
}
