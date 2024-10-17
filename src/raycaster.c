






#include "cub.h"

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
	double	x_start = game->plyr_data.pos_x;
	double	y_start = game->plyr_data.pos_y;
}

int	raycaster(game_s *game)
{
	init_player(game);
	draw_horizon(game);
	compute_ray(game);

	return (0);
}