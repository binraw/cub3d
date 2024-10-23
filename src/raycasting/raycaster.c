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

void draw_wall(game_s *game, double ray_x, double ray_y, int column_index)
{
    double pos_x;
    double pos_y;
	double distance;
	int wall_height;
	int wall_top;
	int wall_bottom;
	int wall_color;
	int y;

	// printf("MUUUUR \n");
	pos_x = game->plyr_data.pos_x;
    pos_y = game->plyr_data.pos_y;
    // 1. Calculer la distance au mur
    distance = sqrt((ray_x - pos_x) * (ray_x - pos_x) + (ray_y - pos_y) * (ray_y - pos_y));
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

void	init_step(ray_s *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = 0;
	}
	else if (ray->dir_x > 0)
	{
		ray->step_x = 1;
		ray->side_x = ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = 0;
	}
	else if (ray->dir_y > 0)
	{
		ray->step_y = 1;
		ray->side_y = ray->delta_y;
	}
	return ;
}

void	init_ray(ray_s *ray, game_s *game, int nb_ray)
{
	 // angle 1er rayon + a gauche + l'incrementation du nb de ray
	ray->angle = (game->plyr_data.angle - (FOV * 0.5)) + nb_ray * (FOV * 0.5);
	// point de depart du rayon
	ray->pos_x = game->plyr_data.pos_x;
	ray->pos_y = game->plyr_data.pos_y;
	// angle du rayon actuelle
	ray->dir_x = cos(ray->angle);
	ray->dir_y = sin(ray->angle);
	// distance du rayon jusqu'a la prochaine intercection vertical et horizontal (valeur positive donc abs)
	ray->delta_x = fabs(1 / ray->dir_x);
	ray->delta_y = fabs(1 / ray->dir_y);
	init_step(ray);
	return ;
}

/*
	DDA ALGO PSEUDO CODE
	* determiner si on doit incrementer abscisse ou ordonne
	* stepx positif == avance a droite (+x) stepx negatif == avance a gauche
	* stepy positif == vers le bas (+x) stepx negatif == vers le haut
		- si ray_dir_x > 0 -> stepx += 1;
		- si ray_dir_x < 0 -> stepx -= 1;
		- si ray_dir_y < 0 -> stepy += 1;
		- si ray_dir_y < 0 -> stepy -= 1;
	
	* calculer distance jusqu'a la lignes de la grille
	* sideDistX est initialiser a la valeur de ray_pos_x (position x initial du player)
	* sideDistY est initialiser a la valeur de ray_pos_y (position y initial du player)
		- sideDistX == distance entre pos joueur et premiere intercection sur axe vertical
		- sideDistY == distance entre pos joueur et premiere intercection sur axe horizontal
	
*/
void	dda(game_s *game, ray_s *ray)
{

}

int	compute_ray(game_s *game)
{
	double	wall_dist;
	ray_s	ray;
	int		i;

	i = 0;
	while (i <= WIN_W)
	{
		// initialise la structure ray suivant i
		init_ray(&ray, game, i);
		ray.hit_wall = false;
		while (ray.hit_wall == false)
		{
			if (ray.side_x < ray.side_y) // croise axe verticale, on avance sur x
			{
				ray.side_x += ray.delta_x;
				ray.pos_x += ray.step_x;
				ray.colision_side = 1;
			}
			else // croise axe horizontal, increment y;
			{
				ray.side_y += ray.delta_y;
				ray.pos_y += ray.step_y;
				ray.colision_side = 0; 
			}
			if (game->map_data.map[(int) round(ray.pos_y)][(int) round(ray.pos_x)] == '1')
			{
				if (i <= 5 || i >= WIN_H - 5)
					printf("HITWALL y = %f : x = %f\n", ray.pos_y, ray.pos_x);
				ray.hit_wall = true;
			}
		}
		// calcul la longueur totale du rayon
		if (ray.colision_side == 1)
			wall_dist = (ray.pos_x - game->plyr_data.pos_x + (1 - ray.step_x) * 0.5) / ray.dir_x;
		else
			wall_dist = (ray.pos_y - game->plyr_data.pos_y + (1 - ray.step_y) * 0.5) / ray.dir_y;
		// coordonnees du point de contact du mur sur la carte
		int x = game->plyr_data.pos_x + ray.dir_x * wall_dist;
		int y = game->plyr_data.pos_y + ray.dir_y * wall_dist;
		draw_wall(game, x, y, i);
		if (i++ <= 5)
			printf("end_y == %d : end_x == %d\n", y ,x);
		else if (i >= WIN_H - 5)
			printf("end_y == %d : end_x == %d\n", y ,x);
	}
	return (0);
}

int	raycaster(game_s *game)
{
	compute_ray(game);
	return (0);
}