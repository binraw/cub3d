#include "cub.h"

static bool	hit_wall(game_s *game, ray_s *ray)
{
    return (ray->pos_x <= 0 || ray->pos_x >= game->map_data.width || \
			ray->pos_y <= 0 || ray->pos_y >= game->map_data.heigth || \
			game->map_data.map[ray->pos_y][ray->pos_x] == '1');
}

static void	dda(game_s *game, ray_s *ray)
{
	while (hit_wall(game, ray) == false)
	{
		if (ray->side_x < ray->side_y) // hit horizontal
		{
			ray->side_x += ray->delta_x;
			ray->pos_x += ray->step_x;
			ray->colision_side = 1;
		}
		else // hit vertical
		{
			ray->side_y += ray->delta_y;
			ray->pos_y += ray->step_y;
			ray->colision_side = 0;
		}
	}
}

int	raycaster(game_s *game)
{
	size_t	i;
	ray_s	ray;
	int		end_x_y[2];

	i = 0;
	while (i < WIN_W)
	{
		game->plyr_data.camera_x = 2 * i / (double)WIN_W - 1;
		init_ray(&ray, game, i);
		dda(game, &ray);
		init_wall_dist(game, &ray, end_x_y);
		if (ray.colision_side == 1)
			draw_wall_ea_we(game, &ray, i, end_x_y);
		else
			draw_wall_no_so(game, &ray, i, end_x_y);
		i++;
	}
	// print_minimap(game, &ray);
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