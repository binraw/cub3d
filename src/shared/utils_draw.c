/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:00:03 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/11/13 13:55:29 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	utils_color(t_game *game, t_ray *ray, int nb, int y_start)
{
	float	hit_x_y[2];
	int		txtr_x_y[2];
	int		index;

	if (ray->colision_side == 1)
	{
		hit_x_y[1] = (game->plyr_data.pos_y / TILE_S)
			+ ray->wall_dist * ray->dir_y;
		hit_x_y[1] -= floor(hit_x_y[1]);
		txtr_x_y[0] = (int)(hit_x_y[1] * game->img_data[nb].width);
	}
	else
	{
		hit_x_y[0] = (game->plyr_data.pos_x / TILE_S)
			+ ray->wall_dist * ray->dir_x;
		hit_x_y[0] -= floor(hit_x_y[0]);
		txtr_x_y[0] = (int)(hit_x_y[0] * game->img_data[nb].width);
	}
	txtr_x_y[1] = ((y_start - game->draw.wall_t) * game->img_data[nb].height)
		/ game->draw.wall_h;
	index = (txtr_x_y[1] * game->img_data[nb].s_line + txtr_x_y[0]
			* (game->img_data[nb].bpp / 8));
	index = define_index(game, nb, index);
	return (*(int *)(game->img_data[nb].data + index));
}

int	define_index(t_game *game, int nb, int index)
{
	if (index < 0)
		index = 0;
	if (index >= game->img_data[nb].s_line * game->img_data[nb].height)
		index = game->img_data[nb].s_line * game->img_data[nb].height - 1;
	return (index);
}
