/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycaster.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:00:09 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/11/13 13:55:29 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline void	init_step(t_ray *ray, t_game *game)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (game->plyr_data.pos_x / TILE_S - ray->pos_x) \
														* ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->pos_x + 1.0 - game->plyr_data.pos_x / TILE_S) \
															* ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (game->plyr_data.pos_y / TILE_S - ray->pos_y) \
														* ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->pos_y + 1.0 - game->plyr_data.pos_y / TILE_S) \
															* ray->delta_y;
	}
}

void	init_ray(t_ray *ray, t_game *game, int nb_ray)
{
	static const double	increment = ANGLE_FOV / WIN_W;

	ray->angle = game->plyr_data.angle - FOV_2 + nb_ray * increment;
	if (ray->angle < 0)
		ray->angle += M_PI * 2;
	else if (ray->angle > M_PI * 2)
		ray->angle -= M_PI * 2;
	ray->dir_x = game->plyr_data.dir_x + game->plyr_data.plane_x * \
											game->plyr_data.camera_x;
	ray->dir_y = game->plyr_data.dir_y + game->plyr_data.plane_y * \
											game->plyr_data.camera_x;
	ray->pos_x = (int) game->plyr_data.pos_x / TILE_S;
	ray->pos_y = (int) game->plyr_data.pos_y / TILE_S;
	ray->delta_x = fabs(1 / ray->dir_x);
	ray->delta_y = fabs(1 / ray->dir_y);
	init_step(ray, game);
	return ;
}
