#include "cub.h"

void	init_step(ray_s *ray, game_s *game)
{
	// printf("dir_x: %f, dir_y: %f, delta_x: %f, delta_y: %f\n", ray->dir_x, ray->dir_y, ray->delta_x, ray->delta_y);
	// printf("step_x: %f, step_y: %f\n", ray->step_x, ray->step_y);
	// printf("side_x: %f, side_y: %f\n", ray->side_x, ray->side_y);

	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (game->plyr_data.pos_x - ray->pos_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->pos_x + 1 - game->plyr_data.pos_x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (game->plyr_data.pos_y - ray->pos_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->pos_y + 1 - game->plyr_data.pos_y) * ray->delta_y;
	}
}

void	init_ray(ray_s *ray, game_s *game, int nb_ray)
{
	ray->pos_x = game->plyr_data.pos_x - TILE_S * 0.5; // on enleve la moitie de la taille de la tuile
	ray->pos_y = game->plyr_data.pos_y - TILE_S * 0.5; // pour lancer les rayons depuis le centre de la case
	// ray->pos_x = game->plyr_data.pos_x + TILE_S; // on enleve la moitie de la taille de la tuile
	// ray->pos_y = game->plyr_data.pos_y + TILE_S;
	if (!nb_ray)
		ray->angle = fmod(game->plyr_data.angle - FOV_2, 2 * M_PI); // angle player - la moitie de l'angle FOV (tout en radian) FOV_2 == 30 degres
	else
		ray->angle += ANGLE_FOV / WIN_W;
	ray->dir_x = cos(ray->angle); // composante horizontale -> direction de x   dirX + planeX * cameraX;
	ray->dir_y = sin(ray->angle); // composante verticale -> direction de y     dirY + planeY * cameraX;
	if (fabs(ray->dir_x) > 0) 
    	ray->delta_x = fabs(1 / ray->dir_x);
	else
    	ray->delta_x = 1e30; // ou une très grande valeur qui indique que le rayon est presque parallèle

	if (fabs(ray->dir_y) > 0)
    	ray->delta_y = fabs(1 / ray->dir_y);
	else
    	ray->delta_y = 1e30;
	init_step(ray, game);
	return ;
}

void	dda(game_s *game, ray_s *ray)
{
	while (ray->hit_wall == false)
	{
		// printf("HERE\n");
		// printf("side_x : %f\n side_y : %f\n", ray->side_x, ray->side_y);
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
		if ((int) ray->pos_x <= 0 || (int) ray->pos_x >= game->map_data.width || \
			(int) ray->pos_y <= 0 || (int) ray->pos_y >= game->map_data.heigth || \
			game->map_data.map[(int) ray->pos_y][(int) ray->pos_x] == '1')
		{
			ray->hit_wall = true;
		}
	}
}

int	compute_ray(game_s *game)
{
    size_t	i;
    double	x_hit;
    double	y_hit;
    double wall_dist;
    ray_s	ray;

	i = 0;
	while (i < WIN_W)
	{
		ray.hit_wall = false;
		// ray.cam_x = 2 * i / (double) WIN_W - 1;
		init_ray(&ray, game, i);
		dda(game, &ray);

        // printf("after DDA\n");
        // print_ray(&ray);

		if(ray.colision_side == 1)
			wall_dist = (ray.pos_x - game->plyr_data.pos_x + (1 - ray.step_x) / 2) / ray.dir_x; 
			// wall_dist = fabs((ray.pos_x - game->plyr_data.pos_x) / ray.dir_x);
		else
			wall_dist = (ray.pos_y - game->plyr_data.pos_y + (1 - ray.step_y) / 2) / ray.dir_y;
			// wall_dist = fabs((ray.pos_y - game->plyr_data.pos_y) / ray.dir_y);
		// double anglediff = ray.angle - game->plyr_data.angle;
		// double correctdist = wall_dist * cos(anglediff);
		// printf("valeur de wall_dist %f\n", wall_dist);
		//compense l’angle entre le joueur et le rayon pour obtenir une distance 
		//perpendiculaire, essentielle pour un rendu 3D correct.
		wall_dist = wall_dist * cos(game->plyr_data.angle - ray.angle);
		if (i == WIN_W)
		{
        	// printf("WALLDIST == %f\n", wall_dist);
			break;
		}
		draw_wall_all(game, &ray, i, wall_dist);
		i++;
	}
	return (0);
}

int	raycaster(game_s *game)
{
	compute_ray(game);
	return (0);
}
