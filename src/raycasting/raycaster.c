#include "cub.h"



// permet de definir l'orientation initial du player :
// void	init_player(game_s *game)
// {
// 	game->plyr_data.angle = ANGLE_N;
// 	if (game->plyr_data.angle == ANGLE_N)
// 	{
// 		game->plyr_data.dir_x = 0;
// 		game->plyr_data.dir_y = -1;
// 	}
// 	else if (game->plyr_data.angle == ANGLE_S)
// 	{
// 		game->plyr_data.dir_x = 0;
// 		game->plyr_data.dir_y = 1;
// 	}
// 	else if (game->plyr_data.angle == ANGLE_E)
// 	{
// 		game->plyr_data.dir_x = 1;
// 		game->plyr_data.dir_y = 0;
// 	}
// 	else
// 	{
// 		game->plyr_data.dir_x = -1;
// 		game->plyr_data.dir_y = 0;
// 	}
// 	game->plyr_data.orientation = game->plyr_data.angle;
// 	game->map_data.tile_size = round((double) WIN_W / game->map_data.width);
// }
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


	pos_x = game->plyr_data.pos_x;
    pos_y = game->plyr_data.pos_y;
    // 1. Calculer la distance au mur
    distance = sqrt((ray_x - pos_x) * (ray_x - pos_x) + (ray_y - pos_y) * (ray_y - pos_y));
	// distance = game->
    // 2. Calculer la hauteur du mur
    wall_height = (int)(WIN_H / distance);
    // 3. Déterminer la position verticale du mur
    wall_top = (WIN_H / 2) - (wall_height / 2);
    wall_bottom = (WIN_H / 2) + (wall_height / 2);
    wall_color = 0;
	y = wall_top;
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

// void	init_step(ray_s *ray)
// {
// 	if (ray->dir_x < 0)
// 	{
// 		ray->step_x = -1;
// 		ray->side_x = 0;
// 	}
// 	else if (ray->dir_x > 0)
// 	{
// 		ray->step_x = 1;
// 		ray->side_x = ray->delta_x;
// 	}
// 	if (ray->dir_y < 0)
// 	{
// 		ray->step_y = -1;
// 		ray->side_y = 0;
// 	}
// 	else if (ray->dir_y > 0)
// 	{
// 		ray->step_y = 1;
// 		ray->side_y = ray->delta_y;
// 	}
// 	return ;
// }

void	init_step(game_s *game, ray_s *ray)
{
    if (ray->dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_x = (ray->pos_x - ray->pos_x) * ray->delta_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_x = (ray->pos_x + 1.0 - ray->pos_x) * ray->delta_x;
    }
    if (ray->dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_y = (ray->pos_y - ray->pos_y) * ray->delta_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_y = (ray->pos_y + 1.0 - ray->pos_y) * ray->delta_y;
    }
    while (!ray->hit_wall)
    {
        if (ray->side_x < ray->side_y)
        {
            ray->side_x += ray->delta_x;
            ray->pos_x += ray->step_x;
            ray->colision_side = 0;
        }
        else
        {
            ray->side_y += ray->delta_y;
            ray->pos_y += ray->step_y;
            ray->colision_side = 1;
        }
        if (game->map_data.map[(int)ray->pos_x][(int)ray->pos_y] == '1')
            ray->hit_wall = 1;
    }
}

void	init_ray(ray_s *ray, game_s *game, int nb_ray)
{
	double camera_x;

	camera_x = 2 * nb_ray / (WIN_W - 1);

	 // angle 1er rayon + a gauche
	if (!nb_ray)
		ray->angle = game->plyr_data.angle - (FOV_RAD) * 0.5;
	else // l'incrementation pour chaque nouveau rayon
		ray->angle += (FOV_RAD) / WIN_W;
	// point de depart du rayon
	ray->pos_x = game->plyr_data.pos_x;
	ray->pos_y = game->plyr_data.pos_y;
	// angle du rayon actuelle
	// ray->dir_x = cos(ray->angle);
	// ray->dir_y = sin(ray->angle);
	ray->dir_x = game->plyr_data.dir_x + game->plyr_data.plane_x * camera_x;
	ray->dir_y = game->plyr_data.dir_y + game->plyr_data.plane_y * camera_x;
	// distance du rayon jusqu'a la prochaine intercection vertical et horizontal (valeur positive donc abs)
	if (ray->dir_x <= 0)
		ray->delta_x = fabs(1 / ray->dir_x);
	else
		ray->delta_x = 1e30;
	if (ray->dir_y <= 0)
		ray->delta_y = fabs(1 / ray->dir_y);
	else
		ray->delta_y = 1e30;
	init_step(game, ray);
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
	while (i < WIN_W)
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
			if ((int) ray.pos_x <= 0 || (int) ray.pos_x >= game->map_data.width || \
				(int) ray.pos_y <= 0 || (int) ray.pos_y >= game->map_data.heigth || \
				game->map_data.map[(int) ray.pos_y][(int) ray.pos_x] == '1')
			{
				// if (i <= 5 || i >= WIN_H - 5)
				// 	printf("HITWALL y = %f : x = %f\n", ray.pos_y, ray.pos_x);
				ray.hit_wall = true;
			}
		}
		// calcul la longueur totale du rayon
		if (ray.colision_side == 1)
			wall_dist = (ray.pos_x - game->plyr_data.pos_x + (1 - ray.step_x) * 0.5) / ray.dir_x;
		else
			wall_dist = (ray.pos_y - game->plyr_data.pos_y + (1 - ray.step_y) * 0.5) / ray.dir_y;
		// coordonnees du point de contact du mur sur la carte
		double x = game->plyr_data.pos_x + ray.dir_x * wall_dist;
		double y = game->plyr_data.pos_y + ray.dir_y * wall_dist;
		draw_wall(game, x, y, i);
		if (i++ <= 5)
			printf("end_y == %f : end_x == %f\n", y ,x);
		else if (i >= WIN_H - 5)
			printf("end_y == %f : end_x == %f\n", y ,x);
	}
	return (0);
}

int	raycaster(game_s *game)
{
	compute_ray(game);
	return (0);
}
