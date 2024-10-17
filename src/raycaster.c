#include "cub.h"



// permet de definir l'orientation initial du player :
void	init_player(game_s *game)
{
	game->plyr_data.angle = ANGLE_N;
	if (game->plyr_data.angle == ANGLE_N)
	{
		game->plyr_data.dir_x = 0;
		game->plyr_data.dir_y = -1;
	}
	else if (game->plyr_data.angle == ANGLE_S)
	{
		game->plyr_data.dir_x = 0;
		game->plyr_data.dir_y = 1;
	}
	else if (game->plyr_data.angle == ANGLE_E)
	{
		game->plyr_data.dir_x = 1;
		game->plyr_data.dir_y = 0;
	}
	else
	{
		game->plyr_data.dir_x = -1;
		game->plyr_data.dir_y = 0;
	}
	game->map_data.tile_size = round((double) WIN_W / game->map_data.width);
	game->plyr_data.pos_x = 21 * TILE_S + TILE_S * 0.5;
	game->plyr_data.pos_y = 3 * TILE_S + TILE_S * 0.5;
}



// permet de faire le visuel actuel avec des ligne et deux zone differentes :
int	draw_horizon(game_s *game)
{
	const int	mid_heigth = WIN_H * 0.5;
	const int	mid_width = WIN_W * 0.5;
	// draw horizontale line
	for (int y = 0; y < WIN_H; y+=2){
		if (y > mid_heigth)
		{
			for (int x = 0; x < WIN_W; x+=2){
				// mlx_pixel_put(MLX_PTR, WIN_PTR, x, y, game->texture.f_color);
				mlx_pixel_put(MLX_PTR, WIN_PTR, x, y, 200);
			}
		}
		else if (y < mid_heigth)
		{
			for (int x = 0; x < WIN_W; x+=2){
				// mlx_pixel_put(MLX_PTR, WIN_PTR, x, y, game->texture.c_color);
				mlx_pixel_put(MLX_PTR, WIN_PTR, x, y, 100);
			}
		}
		else
		{
			for (int x = 0; x < WIN_W; x++){
				mlx_pixel_put(MLX_PTR, WIN_PTR, x, y, 0xffffff);
			}
		}
	}
	//draw verticale line
	for (int y = 0; y < WIN_W; y++){
		mlx_pixel_put(MLX_PTR, WIN_PTR, mid_width, \
						y, 0xffffff);
	}
	return (0);
}

int	compute_ray(game_s *game)
{

	double angle_increment;
	double ray_angle;
	double ray_radians;
	double dir_x;
	double dir_y;
	double ray_x;
	double ray_y;
	int i;

	i = 0;
	angle_increment = FOV / NUM_RAYS; // Angle entre chaque rayon
	ray_angle = game->plyr_data.orientation - (FOV / 2); // Angle du premier rayon
	while (i < NUM_RAYS)
	{
		 // Convertir l'angle en radians
        ray_radians = ray_angle * (M_PI / 180.0);
        // Déterminer la direction du rayon
        dir_x = cos(ray_radians);
        dir_y = sin(ray_radians);
        // Initialiser les coordonnées du rayon
        ray_x = game->plyr_data.pos_x;
        ray_y = game->plyr_data.pos_y;
		// Boucle DDA pour avancer le rayon
        while (true) 
		{
            // Vérifier si le rayon touche un mur
            if (check_wall(ray_x, ray_y, game))
			{
                // Dessiner le mur ici
                draw_wall(game, ray_x, ray_y, i); // i est l'index de colonne
                break ; // Sortir de la boucle si un mur est trouvé
            }
            // Avancer le rayon
            ray_x += dir_x * TILE_S; // Avancer selon la direction
            ray_y += dir_y * TILE_S;
            // Conditions de sortie (si en dehors de la carte)
            if (ray_x < 0 || ray_x >= game->map_data.width * TILE_S ||
                ray_y < 0 || ray_y >= game->map_data.height * TILE_S)
                	break ; // Sortir si le rayon sort des limites
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
    // 4. Dessiner le mur
    wall_color = 0xFFFFFF;
	y = wall_top;
	while(y < wall_bottom)
	{
		if (y >= 0 && y < WIN_H) 
		{ // Vérification des limites de l'écran
            mlx_pixel_put(MLX_PTR, WIN_PTR, column_index, y, wall_color);
        }
		y++;
	}
}

int check_wall(double ray_x, double ray_y, game_s *game) 
{
    // Convertir les coordonnées en indices de la carte
    int map_x = (int)(ray_x / TILE_S);
    int map_y = (int)(ray_y / TILE_S);

    // Vérifier si les indices sont valides et s'il y a un mur
    if (map_x >= 0 && map_x < game->map_data.width &&
        map_y >= 0 && map_y < game->map_data.height)
        return game->map_data.map[map_y][map_x] == 1; // 1 signifie qu'il y a un mur
    return 0; // Pas de mur
}

int	raycaster(game_s *game)
{
	init_player(game);
	// draw_horizon(game);
	compute_ray(game);

	return (0);
}