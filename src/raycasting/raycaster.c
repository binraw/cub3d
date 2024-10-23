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
		mlx_pixel_put(MLX_PTR, WIN_PTR, column_index, y++, 210);
	}
}

void	init_ray(ray_s *ray, game_s *game, int nb_ray)
{
	ray->angle = (game->plyr_data.angle - (FOV * 0.5)) + nb_ray * (FOV * 0.5); // angle 1er rayon + a gauche
	ray->pos_x = game->plyr_data.pos_x;
	ray->pos_y = game->plyr_data.pos_y;
	ray->dir_x = cos(ray->angle);
	ray->dir_y = sin(ray->angle);
	ray->delta_x = abs(1 / ray->dir_x);
	ray->delta_y = abs(1 / ray->dir_y);
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
void	dda(game_s, *game, ray_s *ray)
{
	double	stepx;
	double	stepy;

	stepx = ray->pos_x;
	stepy = ray->pos_y;
	if (ray->dir_x > 0)
		stepx = 1;
	else if (ray->dir_x < 0)
		stepx = 1;
	if (ray->dir_y > 0)
		stepy = 1;
	else if (ray->dir_y > 0)
		stepy = 1;
	
}

int	compute_ray(game_s *game)
{
	ray_s	ray;
	int		i;

	i = 0;
	while (i <= WIN_W)
	{
		init_ray(&ray, game, i);
		





        while (ray_x > 0 && ray_y > 0) 
		{
            if (check_wall(ray_x, ray_y, game) == 1)
			{
                draw_wall(game, ray_x, ray_y, i); // i est l'index de colonne
                break ;
            }
            // Avancer le rayon
            ray_x += ray_dirx * TILE_S; // Avancer selon la direction
            ray_y += ray_diry * TILE_S;
			// printf("Ray %d: Ray_x: %f, Ray_y: %f\n", i, ray_x, ray_y);
            if (ray_x < 0 || ray_x >= game->map_data.width * TILE_S ||
                ray_y < 0 || ray_y >= game->map_data.heigth * TILE_S)
                	break ;
        }
		i++;
		curr_ray_angle = ray.angle + i * (FOV / WIN_W);n
		ray.pos_x = game->plyr_data.pos_x;
        ray.pos_y = game->plyr_data.pos_y;
		ray.dir_x = cos(ray.angle);
		ray.dir_y = sin(ray.angle);
	}
	return (0);
}

int	raycaster(game_s *game)
{
	compute_ray(game);
	return (0);
}