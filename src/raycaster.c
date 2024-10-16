



#include "cub.h"

const int	mid_heigth = WIN_H * 0.5;
const int	mid_width = WIN_W * 0.5;

int	init_raycaster(game_s *game)
{
	game->plyr_data.mov_speed = 2;
	game->plyr_data.rot_speed = 0.5;
	game->plyr_data.orientation = A_NORTH;
	game->plyr_data.pos_x = 21 * TILE_S + TILE_S * 0.5;
	game->plyr_data.pos_y = 3 * TILE_S + TILE_S * 0.5;
	game->plyr_data.angle_fov = game->plyr_data.orientation - A_FOV / 2;
	game->map_data.tile_size = round((double) WIN_W / game->map_data.width);
	printf("tile size = %d\n", game->map_data.tile_size);
	return (0);
}

int	draw_horizon(game_s *game)
{
	// draw horizontale line
	for (int y = 0; y < WIN_H; y+=2){
		if (y > mid_heigth)
		{
			for (int x = 0; x < WIN_W; x+=2){
				mlx_pixel_put(MLX_PTR, WIN_PTR, x, y, game->texture.f_color);
			}
		}
		else if (y < mid_heigth)
		{
			for (int x = 0; x < WIN_W; x+=2){
				mlx_pixel_put(MLX_PTR, WIN_PTR, x, y, game->texture.c_color);
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

int	find_wall(game_s *game)
{
	return (0);
}

int	raycaster(game_s *game)
{
	init_raycaster(game);
	draw_horizon(game);
	find_wall(game);



	return (0);
}