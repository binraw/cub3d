#include "cub.h"



int check_wall(double ray_x, double ray_y, game_s *game)
{
	int map_x;
	int map_y;

    map_x = (int) round(ray_x);
    map_y = (int) round(ray_y);
    if (map_x >= 0 && map_x < game->map_data.width &&
        map_y >= 0 && map_y < game->map_data.heigth)
	{
		return (game->map_data.map[map_y][map_x] == '1');
	}
    return (0);
}

void draw_wall(game_s *game, double ray_x, double ray_y, int column_index, double distance)
{
	int wall_height;
	int wall_top;
	int wall_bottom;
	int wall_color;
	int y;

    // distance = sqrt((ray_x - pos_x) * (ray_x - pos_x) + (ray_y - pos_y) * (ray_y - pos_y));

    wall_height = (int)(WIN_H / distance);
    wall_top = (WIN_H / 2) - (wall_height / 2);
    wall_bottom = (WIN_H / 2) + (wall_height / 2);
    wall_color = 0;
	y = wall_top;
	while(y < wall_bottom)
	{
		if (y >= 0 && y < WIN_H)
		{
            mlx_pixel_put(MLX_PTR, WIN_PTR, column_index, y, wall_color);
        }
		y++;
	}
	y = 0;
	while (y < wall_top)
	{
		if (y >= 0 && y < WIN_H)
		{
            mlx_pixel_put(MLX_PTR, WIN_PTR, column_index, y, 200);
        }
		y++;
	}
	y = wall_bottom;
	while(y < WIN_H)
	{
		mlx_pixel_put(MLX_PTR, WIN_PTR, column_index, y++, 300);
	}
}

void	init_step(ray_s *ray, game_s *game)
{
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
	else if (ray->dir_y > 0)
	{
		ray->step_y = 1;
		ray->side_y = (ray->pos_y + 1 - game->plyr_data.pos_y) * ray->delta_y;
	}
	else
    {
        ray->step_y = 0; // Si dir_y est 0, on ne bouge pas sur l'axe Y
        ray->side_y = 1e30; // Éviter la division par zéro
    }
	// return ;
}

void	init_ray(ray_s *ray, game_s *game, int nb_ray)
{

	ray->pos_x = game->plyr_data.pos_x - TILE_S * 0.5; // on enleve la moitie de la taille de la tuile
	ray->pos_y = game->plyr_data.pos_y - TILE_S * 0.5; // pour lancer les rayons depuis le centre de la case

	if (!nb_ray)
	{
		printf("RENTRE ICIIIIII \n");
		ray->angle = fmod(game->plyr_data.angle - FOV_2, 2*M_PI); // angle player - la moitie de l'angle FOV (tout en radian) FOV_2 == 30 degres
		ray->plane_x = -0.66; // vecteur du plan joueur
		ray->plane_y = 0; 
	}
	ray->cam_x = (2 * nb_ray / (double) WIN_W) - 1;
	ray->dir_x = game->plyr_data.dir_x + ray->plane_x * ray->cam_x; // composante horizontale -> direction de x   dirX + planeX * cameraX;
	ray->dir_y = game->plyr_data.dir_y + ray->plane_y * ray->cam_x; // composante verticale -> direction de y     dirY + planeY * cameraX;
	if (ray->dir_x != 0)
		ray->delta_x = fabs(1 / ray->dir_x);
	else
		ray->delta_x = 1e30;
	if (ray->dir_y != 0)
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
	double	wall_dist;
	ray_s	ray;
	int		i;

	i = 0;
	while (i < WIN_W)
	{
		// initialise la structure ray suivant i
		ray.hit_wall = false;
		// ray.cam_x = 2 * i / (double) WIN_W - 1;
		init_ray(&ray, game, i);
		// calcul la longueur totale du rayon walldist == longueur rayon
		dda(game, &ray);

		if(ray.colision_side == 1)
			wall_dist = (ray.side_x - ray.delta_x);
		else
			wall_dist = (ray.side_y - ray.delta_y);

		// // correction fisheye
		// // double anglediff = ray.angle - game->plyr_data.angle;
		// // double correctdist = wall_dist * cos(anglediff);

		// // // coordonnees du point de contact du mur sur la carte
		// // double x = game->plyr_data.pos_x + ray.dir_x * wall_dist;
		// // double y = game->plyr_data.pos_y + ray.dir_y * wall_dist;
		draw_wall(game, POS_X(game), POS_Y(game), i, wall_dist);
		i++;
	}
	return (0);
}

int	raycaster(game_s *game)
{
	compute_ray(game);
	return (0);
}