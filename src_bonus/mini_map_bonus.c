
#include "cub.h"

static inline void	print_case(game_s *game, int color)
{
	static int	y;
	static int	x;
	const int	tmp_y = y + M_TILE_S;
	const int	tmp_x = x + M_TILE_S;

	while (y < tmp_y)
	{
		while (x < tmp_x)
		{
			my_mlx_pixel_put(&game->img, x, y, color);
			x++;
		}
		y++;
		if (y < tmp_y)
			x = tmp_x - M_TILE_S;
	}
	if (y == M_TILE_S * (M_TILE_S + 1) && x == M_TILE_S * (M_TILE_S + 1))
	{
		y = 0;
		x = 0;
	}
	else if (y == tmp_y && x < M_TILE_S * (M_TILE_S + 1))
		y -= M_TILE_S;
	else if (y == tmp_y && x == M_TILE_S * (M_TILE_S + 1))
		x = 0;
}

static inline int	color_choice(game_s *game, int x, int y, const int *ply_x_y)
{
	const size_t	height = game->map_data.heigth;
	const size_t	width = game->map_data.width;

	if (x == ply_x_y[0] && y == ply_x_y[1])
		return (RED);
	if (y >= 0 && y < height && x >= 0 && x < width && \
			game->map_data.map[y][x] != '1' && game->map_data.map[y][x] != ' ')
		return (game->draw.floor_c >> 1);
	else if (y >= 0 && y < height && x >= 0 && \
								x < width && game->map_data.map[y][x] == '1')
		return (game->draw.ceiling_c >> 1);
	else
		return (game->draw.floor_c >> 2);
}

void	print_minimap(game_s *game, ray_s *ray)
{
    static const int    m_tile_s = (M_TILE_S >> 1);
	int			x;
	int			y;
	const int	ply_x_y[2] = {(int) game->plyr_data.pos_x / TILE_S, \
							(int) game->plyr_data.pos_y / TILE_S};

	x = ply_x_y[0] - m_tile_s;
	y = ply_x_y[1] - m_tile_s;
	while (y <= ply_x_y[1] + m_tile_s)
	{
		while (x <= ply_x_y[0] + m_tile_s)
			print_case(game, color_choice(game, x++, y, ply_x_y));
		x = ply_x_y[0] - m_tile_s;
		y++;
	}
}
