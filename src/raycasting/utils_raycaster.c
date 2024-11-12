



#include "cub.h"

static void	find_ray_impact(game_s *game, ray_s *ray, int *end_x_y, int nb_txtr)
{
	end_x_y[0] = game->plyr_data.pos_x + ray->dir_x * ray->wall_dist * \
									game->img_data[nb_txtr].width;
	end_x_y[1] = game->plyr_data.pos_y + ray->dir_y * ray->wall_dist * \
									game->img_data[nb_txtr].height;
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

void	init_wall_dist(game_s *game, ray_s *ray, int *end_x_y)
{
	if (ray->colision_side == 1)
	{
		ray->wall_dist = (ray->pos_x - game->plyr_data.pos_x / TILE_S + \
									((1 - ray->step_x) >> 1)) / ray->dir_x;
		if (ray->dir_y < 0)
			find_ray_impact(game, ray, end_x_y, 1);
		else
			find_ray_impact(game, ray, end_x_y, 0);
	}
	else
	{
		ray->wall_dist = (ray->pos_y - game->plyr_data.pos_y / TILE_S + \
									((1 - ray->step_y) >> 1)) / ray->dir_y;
		if (ray->dir_x < 0)
			find_ray_impact(game, ray, end_x_y, 3);
		else
			find_ray_impact(game, ray, end_x_y, 2);
	}
}

void	init_ray(ray_s *ray, game_s *game, int nb_ray)
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
