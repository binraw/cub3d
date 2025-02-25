/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:00:25 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/11/13 16:24:09 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline bool	hit_wall(t_game *game, t_ray *ray)
{
	return (ray->pos_x <= 0 || ray->pos_x >= (int)game->map_data.width || \
			ray->pos_y <= 0 || ray->pos_y >= (int)game->map_data.heigth || \
			game->map_data.map[ray->pos_y][ray->pos_x] == '1');
}

static inline void	init_wall_dist(t_game *game, t_ray *ray)
{
	if (ray->colision_side == 1)
	{
		ray->wall_dist = (ray->pos_x - game->plyr_data.pos_x / TILE_S + \
									((1 - ray->step_x) >> 1)) / ray->dir_x;
	}
	else
	{
		ray->wall_dist = (ray->pos_y - game->plyr_data.pos_y / TILE_S + \
									((1 - ray->step_y) >> 1)) / ray->dir_y;
	}
}

static inline void	dda(t_game *game, t_ray *ray)
{
	while (hit_wall(game, ray) == false)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->pos_x += ray->step_x;
			ray->colision_side = 1;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->pos_y += ray->step_y;
			ray->colision_side = 0;
		}
	}
}

static inline int	raycaster(t_game *game)
{
	size_t	i;
	t_ray	ray;

	i = 0;
	while (i < WIN_W)
	{
		game->plyr_data.camera_x = 2 * i / (double) WIN_W - 1;
		init_ray(&ray, game, i);
		dda(game, &ray);
		init_wall_dist(game, &ray);
		draw_column(game, &ray, i);
		i++;
	}
	mlx_put_image_to_window(game->console.mlx_ptr, game->console.win_ptr,
		game->img.img_ptr, 0, 0);
	return (0);
}

int	loop_hook(t_game *game)
{
	if (game->plyr_data.write == 0)
	{
		raycaster(game);
		game->plyr_data.write = 1;
	}
	if (game->plyr_data.move_up || game->plyr_data.move_down || \
		game->plyr_data.move_left || game->plyr_data.move_right || \
		game->plyr_data.rotate_l || game->plyr_data.rotate_r)
	{
		if (update_movement(game) == 1)
			return (0);
		raycaster(game);
	}
	return (0);
}
