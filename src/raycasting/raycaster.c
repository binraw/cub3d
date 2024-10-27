#include "cub.h"



int check_wall(double ray_x, double ray_y, game_s *game)
{
    // Convertir les coordonnées en indices de la carte
	int map_x;
	int map_y;

    map_x = (int) round(ray_x);
    map_y = (int) round(ray_y);
    // Vérifier si les indices sont valides et s'il y a un mur
    if (map_x >= 0 && map_x < game->map_data.width &&
        map_y >= 0 && map_y < game->map_data.heigth)
	{
		// printf("HIT WALL\n");
		return (game->map_data.map[map_y][map_x] == '1');
	}
    return (0); // Pas de mur
}

void draw_wall(game_s *game, double ray_x, double ray_y, int column_index, double distance)
{
	int wall_height;
	int wall_top;
	int wall_bottom;
	int wall_color;
	int y;

	// printf("MUUUUR \n");
    // 1. Calculer la distance au mur
    // distance = sqrt((ray_x - pos_x) * (ray_x - pos_x) + (ray_y - pos_y) * (ray_y - pos_y));
    // 2. Calculer la hauteur du mur
    wall_height = (int)(WIN_H / distance);
	// printf("valeur de la hauteur du mur : %d\n", wall_height);
    // 3. Déterminer la position verticale du mur
    wall_top = (WIN_H / 2) - (wall_height / 2);
    wall_bottom = (WIN_H / 2) + (wall_height / 2);
    // 4. Dessiner le mur
    wall_color = 0;
	y = wall_top;
	// printf("valeur wall top : %d\n", wall_top);
	// printf("valeur wall botton : %d\n", wall_bottom);
	while(y < wall_bottom)
	{
		if (y >= 0 && y < WIN_H)
		{ // Vérification des limites de l'écran
            mlx_pixel_put(MLX_PTR, WIN_PTR, column_index, y, wall_color);
        }
		y++;
	}
	// plafond :
	y = 0; // represente le haut de l'ecran
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
	return ;
}

void	init_ray(ray_s *ray, game_s *game, int nb_ray)
{
    // static const tile = TILE_S * 0.5;
    // point de depart du rayon
	ray->pos_x = game->plyr_data.pos_x - TILE_S * 0.5; // on enleve la moitie de la taille de la tuile
	ray->pos_y = game->plyr_data.pos_y - TILE_S * 0.5; // pour lancer les rayons depuis le centre de la case
	// angle 1er rayon + a gauche
    // fmod permet de faire un modulo sur des float
    // on assure que angle soit toujours dans le bon range (entre 0 et 2 * PI)
	if (!nb_ray)
	{
		ray->angle = fmod(game->plyr_data.angle - FOV_2, 2*M_PI); // angle player - la moitie de l'angle FOV (tout en radian) FOV_2 == 30 degres
		ray->plane_x = -0.66; // vecteur du plan joueur
		ray->plane_y = 0; // oriantation nord
	}
	// else // l'incrementation pour chaque nouveau rayon
	// 	ray->angle += ((FOV / 180) * M_PI) / WIN_W;

	// les valeurs combinnees de cos et sin forment le vecteur de direction
	ray->dir_x = game->plyr_data.dir_x + ray->plane_x * ray->cam_x; // composante horizontale -> direction de x   dirX + planeX * cameraX;
	ray->dir_y = game->plyr_data.dir_y + ray->plane_y * ray->cam_x; // composante verticale -> direction de y     dirY + planeY * cameraX;

	// distance du rayon jusqu'a la prochaine intercection vertical et horizontal (valeur positive donc abs)
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

/*
	DDA ALGO PSEUDO CODE
	* determiner si on doit incrementer abscisse ou ordonne
	* stepx positif == avance a droite (+x) stepx negatif == avance a gauche
	* stepy positif == vers le bas (+x) stepx negatif == vers le haut
		- si ray_dir_x > 0 -> stepx = 1;
		- si ray_dir_x < 0 -> stepx = -1;
		- si ray_dir_y < 0 -> stepy = 1;
		- si ray_dir_y < 0 -> stepy = -1;

	* calculer distance jusqu'a la lignes de la grille
	* sideDistX est initialiser a la valeur de ray_pos_x (position x initial du player)
	* sideDistY est initialiser a la valeur de ray_pos_y (position y initial du player)
		- sideDistX == distance entre pos joueur et premiere intercection sur axe vertical
		- sideDistY == distance entre pos joueur et premiere intercection sur axe horizontal

*/
void	dda(game_s *game, ray_s *ray)
{
	while (ray->hit_wall == false)
	{
		if (ray->side_x < ray->side_y) // croise axe verticale, on avance sur x
		{
			ray->side_x += ray->delta_x;
			ray->pos_x += ray->step_x;
			ray->colision_side = 1;
		}
		else // croise axe horizontal, increment y;
		{
			ray->side_y += ray->delta_y;
			ray->pos_y += ray->step_y;
			ray->colision_side = 0;
		}
		if ((int) ray->pos_x <= 0 || (int) ray->pos_x >= game->map_data.width || \
			(int) ray->pos_y <= 0 || (int) ray->pos_y >= game->map_data.heigth || \
			game->map_data.map[(int) ray->pos_y][(int) ray->pos_x] == '1')
		{
			// printf("HIT WALL\n");
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
		ray.cam_x = 2 * i / (double) WIN_W - 1;
		init_ray(&ray, game, i);
		// calcul la longueur totale du rayon walldist == longueur rayon
		// dda(game, &ray);

		// if(ray.colision_side == 1)
		// 	wall_dist = (ray.side_x - ray.delta_x);
		// else
		// 	wall_dist = (ray.side_y - ray.delta_y);

		// // correction fisheye
		// // double anglediff = ray.angle - game->plyr_data.angle;
		// // double correctdist = wall_dist * cos(anglediff);

		// // // coordonnees du point de contact du mur sur la carte
		// // double x = game->plyr_data.pos_x + ray.dir_x * wall_dist;
		// // double y = game->plyr_data.pos_y + ray.dir_y * wall_dist;
		// draw_wall(game, POS_X(game), POS_Y(game), i, wall_dist);
		i++;
		// if (i++ <= 5)
		// 	printf("end_y == %f : end_x == %f\n", y ,x);
		// else if (i >= WIN_H - 5)
		// 	printf("end_y == %f : end_x == %f\n", y ,x);
		// else if (i == 500)
		// 	printf("middle end_y == %f : end_x == %f : angle == %f\n", y ,x, ray.angle);
	}
	return (0);
}

int	raycaster(game_s *game)
{
	compute_ray(game);
	return (0);
}
