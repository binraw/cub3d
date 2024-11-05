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

static void	init_step(ray_s *ray, game_s *game)
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

static void	init_ray(ray_s *ray, game_s *game, int nb_ray)
{
	static const double	increment = ANGLE_FOV / WIN_W;

	ray->angle = game->plyr_data.angle - FOV_2 + nb_ray * increment;
	if (ray->angle < 0)
		ray->angle += M_PI * 2;
	else if (ray->angle > M_PI * 2)
		ray->angle -= M_PI * 2;
	ray->dir_x = game->plyr_data.dir_x + game->plyr_data.plane_x * game->plyr_data.camera_x;
	ray->dir_y = game->plyr_data.dir_y + game->plyr_data.plane_y * game->plyr_data.camera_x;
	ray->pos_x = (int) game->plyr_data.pos_x / TILE_S;
	ray->pos_y = (int) game->plyr_data.pos_y / TILE_S;
	ray->delta_x = fabs(1 / ray->dir_x);
	ray->delta_y = fabs(1 / ray->dir_y);
	init_step(ray, game);
	return ;
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
		init_wall_dist(game, &ray);
		end_x_y[0] = game->plyr_data.pos_x + ray.dir_x * ray.wall_dist * TILE_S;
		end_x_y[1] = game->plyr_data.pos_y + ray.dir_y * ray.wall_dist * TILE_S;
		if (ray.colision_side == 1)
			draw_wall_ea_we(game, &ray, i, end_x_y);
		else
			draw_wall_no_so(game, &ray, i, end_x_y);
		i++;
	}
	print_minimap(game, &ray);
	return (0);
}
void	init_wall_dist(game_s *game, ray_s *ray)
{
	if (ray->colision_side == 1)
			ray->wall_dist = (ray->pos_x - game->plyr_data.pos_x / TILE_S + \
										(1 - ray->step_x) * 0.5) / ray->dir_x;
		else
			ray->wall_dist = (ray->pos_y - game->plyr_data.pos_y / TILE_S + \
										(1 - ray->step_y) * 0.5) / ray->dir_y;
}
