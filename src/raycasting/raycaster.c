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

int	compute_ray(game_s *game)
{

	double angle_increment;
	double ray_angle;
	double ray_radians;
	double ray_x;
	double ray_y;
	int i;
	// printf("rentre bien dans compute\n");
	i = 0;
	angle_increment = FOV / WIN_W;
	ray_angle = game->plyr_data.orientation - (FOV / 2);
	while (i < WIN_W)
	{
		 // Convertir l'angle en radians
        ray_radians = ray_angle * (ANGLE_W / 180.0);
        game->plyr_data.dir_x = cos(ray_radians);
        game->plyr_data.dir_y = sin(ray_radians);
        ray_x = game->plyr_data.pos_x;
        ray_y = game->plyr_data.pos_y;
		// printf("valeur de ray_x ray_y :%f\n %f\n", ray_x, ray_y);
        while (true && ray_x > 0 && ray_y > 0) 
		{
            if (check_wall(ray_x, ray_y, game) == 1)
			{
                draw_wall(game, ray_x, ray_y, i); // i est l'index de colonne
                break ;
            }
            // Avancer le rayon
            ray_x += game->plyr_data.dir_x * TILE_S; // Avancer selon la direction
            ray_y += game->plyr_data.dir_y * TILE_S;
			// printf("Ray %d: Ray_x: %f, Ray_y: %f\n", i, ray_x, ray_y);
            if (ray_x < 0 || ray_x >= game->map_data.width * TILE_S ||
                ray_y < 0 || ray_y >= game->map_data.heigth * TILE_S)
                	break ;
        }
		ray_angle += angle_increment;
		i++;
	}
	return (0);
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
	while (y < WIN_H)
	{
		if (y >= 0 && y < WIN_H)
		{
            mlx_pixel_put(MLX_PTR, WIN_PTR, column_index, y, 100);
        }
		y++;
	}
}

int check_wall(double ray_x, double ray_y, game_s *game) 
{
    // Convertir les coordonnées en indices de la carte
	int map_x;
	int map_y;

    // map_x = (int)(ray_x / TILE_S);
    // map_y = (int)(ray_y / TILE_S);
	map_x = (int)(ray_x);
    map_y = (int)(ray_y);
    // Vérifier si les indices sont valides et s'il y a un mur
    if (map_x >= 0 && map_x < game->map_data.width &&
        map_y >= 0 && map_y < game->map_data.heigth)
		{
			return (game->map_data.map[map_y][map_x] == '1');
		}
    return (0); // Pas de mur
}

int	raycaster(game_s *game)
{
	compute_ray(game);
	return (0);
}