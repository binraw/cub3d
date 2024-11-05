
#include "cub.h"

void	print_case(game_s *game, bool is_floor, int start_x, int start_y)
{
	int	curr_color;
	int	tmp_x_y[2];
	const int	cell_w = (WIN_W / 7) / game->map_data.width;
	const int	cell_h = (WIN_H / 7) / game->map_data.heigth;

	if (is_floor)
		curr_color = 0;
	else
		curr_color = 0xFFFFFF;
	start_x *= cell_w;
	start_y *= cell_h;
	tmp_x_y[0] = start_x;
	tmp_x_y[1] = start_y;

	// print_constante(game);
	while (start_y < tmp_x_y[1] + cell_h)
	{
		while (start_x < tmp_x_y[0] + cell_w)
		{
			mlx_pixel_put(MLX_PTR, WIN_PTR, start_x, start_y, curr_color);
			start_x += 1;
		}
		start_x = tmp_x_y[0];
		start_y++;
	}
}

void    print_minimap(game_s *game, ray_s *ray)
{
	size_t	y = 0;
	size_t	x = 0;

	while (game->map_data.map[y])
	{
		while (game->map_data.map[y][x])
		{
			if (game->map_data.map[y][x] != ' ' && game->map_data.map[y][x] != '1')
				print_case(game, 1, x, y); // floor
			else if (game->map_data.map[y][x] == '1')
				print_case(game, 0, x, y); // waal
			x++;
		}
		x = 0;
		y++;
	}
}
