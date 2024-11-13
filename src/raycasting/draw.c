/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:00:42 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/11/13 09:55:40 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	my_mlx_pixel_put(img_s *data, int x, int y, int color)
{
	((int *)data->data)[y * (data->s_line >> 2) + x] = color;
}

static inline void	draw_sky_floor(game_s *game, int column_index, \
											int wall_top, int wall_bottom)
{
	int	y;

	y = 0;
	if (wall_top < WIN_H)
	{
		while (y < wall_top)
			my_mlx_pixel_put(&game->img, column_index, y++,
				game->draw.ceiling_c);
	}
	y = 0;
	if (wall_bottom > 0)
	{
		y = wall_bottom;
		while (y < WIN_H)
			my_mlx_pixel_put(&game->img, column_index, y++,
				game->draw.floor_c);
	}
}

static inline int	get_color(game_s *game, ray_s *ray, int y_start)
{
	if (ray->colision_side == 1 && ray->dir_x < 0)
		return (utils_color(game, ray, 3, y_start));
	else if (ray->colision_side == 1)
		return (utils_color(game, ray, 2, y_start));
	else if (ray->dir_y < 0)
		return (utils_color(game, ray, 1, y_start));
	else
		return (utils_color(game, ray, 0, y_start));
	return (0);
}

void	draw_column(game_s *game, ray_s *ray, int col_index)
{
	static const int	mid_win = WIN_H >> 1;
	int					y_start;

	if (ray->wall_dist <= 0)
		game->draw.wall_h = WIN_H;
	else
		game->draw.wall_h = (int)(WIN_H / ray->wall_dist);
	game->draw.wall_t = (mid_win) - (game->draw.wall_h >> 1);
	game->draw.wall_b = (mid_win) + (game->draw.wall_h >> 1);
	y_start = game->draw.wall_t;
	while (y_start < game->draw.wall_b)
	{
		if (y_start >= 0 && y_start < WIN_H)
		{
			my_mlx_pixel_put(&game->img, col_index, y_start, \
									get_color(game, ray, y_start));
		}
		y_start++;
	}
	draw_sky_floor(game, col_index, game->draw.wall_t, game->draw.wall_b);
}
