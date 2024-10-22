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

int	compute_ray(game_s *game)
{
	double	ray_angle;
	double	ray_dirx;
	double	ray_diry;
	double	ray_radians;

	double ray_x;
	double ray_y;
	int i;
	
	// printf("in compute_ray\n");
	i = 0;
	ray_angle = game->plyr_data.angle - (FOV * 0.5);
	ray_dirx = cos(ray_angle);
	ray_diry = sin(ray_angle);
	while (i < WIN_W)
	{
		 // Convertir l'angle du rayon en radians
        ray_radians = (ray_angle * M_PI) / 180;
		// reinitialise le point de depart du rayon sur la pos du player
		ray_x = game->plyr_data.pos_x;
        ray_y = game->plyr_data.pos_y;
        while (true && ray_x > 0 && ray_y > 0) 
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
		ray_angle += i - (FOV * 0.5);
		i++;
	}
	return (0);
}

int	raycaster(game_s *game)
{
	compute_ray(game);
	return (0);
}