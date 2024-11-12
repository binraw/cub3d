#include "cub.h"

static inline bool	hit_wall(game_s *game, ray_s *ray)
{
    return (ray->pos_x <= 0 || ray->pos_x >= game->map_data.width || \
			ray->pos_y <= 0 || ray->pos_y >= game->map_data.heigth || \
			game->map_data.map[ray->pos_y][ray->pos_x] == '1');
}

static inline void	init_wall_dist(game_s *game, ray_s *ray)
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

static inline void	dda(game_s *game, ray_s *ray)
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

static inline int	raycaster(game_s *game)
{
	size_t	i;
	ray_s	ray;

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
	print_minimap(game, &ray);
	mlx_put_image_to_window(MLX_PTR, WIN_PTR, game->img.img_ptr, 0, 0);
	return (0);
}

int loop_hook(game_s *game)
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
