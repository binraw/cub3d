#include "cub.h"

static inline int utils_color(game_s *game, ray_s *ray, int nb, int *end_x_y)
{
    int txtr_y;
    int txtr_x;
    int index;

	if (ray->colision_side == 1)
    {
        end_x_y[1] = end_x_y[1] % TILE_S;
        txtr_x = (end_x_y[1] * game->img_data[nb].width) / TILE_S;
        // txtr_x = end_x_y[1] % game->img_data[nb].width;
    }
		
	else
    {
        end_x_y[0] = end_x_y[0] % TILE_S;
        txtr_x = (end_x_y[0] * game->img_data[nb].width) / TILE_S;
    }
		// txtr_x = end_x_y[0] % game->img_data[nb].width;
    txtr_y = ((game->draw.i - game->draw.wall_t) * game->img_data[nb].height) / game->draw.wall_h;
    index = (txtr_y * game->img_data[nb].s_line + txtr_x * (game->img_data[nb].bpp / 8)); // bpp / 8 pour obtenir le nombre d'octets par pixel
    return (*(int *)(game->img_data[nb].data + index));
}

static inline int	get_color(game_s *game, ray_s *ray, int *end_x_y)
{
    if (ray->colision_side == 1 && ray->dir_x < 0) // west
        return (utils_color(game, ray, 2, end_x_y));
    else if (ray->colision_side == 1) // east
        return (utils_color(game, ray, 3, end_x_y));
    else if (ray->dir_y < 0) // south wall
        return (utils_color(game, ray, 1, end_x_y));
    else // north wall
        return (utils_color(game, ray, 0, end_x_y));
    return (0);
}
inline void    my_mlx_pixel_put(img_s *data, int x, int y, int color)
{
    ((int *)data->data)[y * (data->s_line >> 2) + x] = color;
}

static inline void	draw_sky_floor(game_s *game, int column_index, int wall_top, int wall_bottom)
{
    int y;

    y = 0;
    if (wall_top < WIN_H)
    {
        while (y < wall_top)
        {
            my_mlx_pixel_put(&game->img, column_index, y, game->draw.ceiling_c);
            // mlx_pixel_put(MLX_PTR, WIN_PTR, column_index, y, \
            //                             game->draw.ceiling_c);
        
            y++;
        }
    }
    y = 0;
    if (wall_bottom > 0)
    {
        y = wall_bottom;
        while(y < WIN_H)
        {
            my_mlx_pixel_put(&game->img, column_index, y, game->draw.floor_c);
            // mlx_pixel_put(MLX_PTR, WIN_PTR, column_index, y, \
            //                                 game->draw.floor_c);
            y++;
        }
    }
}


void	draw_column(game_s *game, ray_s *ray, int col_index, int *end_x_y)
{
	static const int	mid_win = WIN_H >> 1;

    if (ray->wall_dist <= 0)
            game->draw.wall_h = WIN_H;
    else
        game->draw.wall_h = (int) (WIN_H / ray->wall_dist);
    game->draw.wall_t = (int) (floor((mid_win) - (game->draw.wall_h >> 1)));
    game->draw.wall_b = (int) (floor((mid_win) + (game->draw.wall_h >> 1)));
	game->draw.i = game->draw.wall_t;
    while (game->draw.i < game->draw.wall_b)
    {
        if (game->draw.i >= 0 && game->draw.i < WIN_H)
        {
            my_mlx_pixel_put(&game->img, col_index, game->draw.i, get_color(game, ray, end_x_y));
			// mlx_pixel_put(MLX_PTR, WIN_PTR, col_index, game->draw.i, \
			// 							get_color(game, ray, end_x_y));
        }
        game->draw.i++;
    }
    draw_sky_floor(game, col_index, game->draw.wall_t, game->draw.wall_b);
}
