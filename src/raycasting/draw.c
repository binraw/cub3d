#include "cub.h"

static int	get_color(game_s *game, ray_s *ray, int txtr_y, int index)
{
    if (ray->colision_side == 1 && ray->dir_x < 0) // west
    {
        txtr_y = ((game->draw.i - game->draw.wall_t) * game->img_data[2].height) / game->draw.wall_h;
        index = (txtr_y * game->img_data[2].s_line + game->draw.txtr_x * (game->img_data[2].bpp / 8)); // bpp / 8 pour obtenir le nombre d'octets par pixel
        game->draw.color = *(int *)(game->img_data[2].data + index);
    }
    else if (ray->colision_side == 1) // east
    {
        txtr_y = ((game->draw.i - game->draw.wall_t) * game->img_data[3].height) / game->draw.wall_h;
        index = (txtr_y * game->img_data[3].s_line + game->draw.txtr_x * (game->img_data[3].bpp / 8)); // bpp / 8 pour obtenir le nombre d'octets par pixel
        game->draw.color = *(int *)(game->img_data[3].data + index);
    }
    else if (ray->dir_y < 0) // south wall
    {
        txtr_y = ((game->draw.i - game->draw.wall_t) * game->img_data[1].height) / game->draw.wall_h;
        index = (txtr_y * game->img_data[1].s_line + game->draw.txtr_x * (game->img_data[1].bpp / 8)); // bpp / 8 pour obtenir le nombre d'octets par pixel
        game->draw.color = *(int *)(game->img_data[1].data + index);
    }
    else // north wall
    {
        txtr_y = ((game->draw.i - game->draw.wall_t) * game->img_data[0].height) / game->draw.wall_h;
        index = (txtr_y * game->img_data[0].s_line + game->draw.txtr_x * (game->img_data[0].bpp / 8)); // bpp / 8 pour obtenir le nombre d'octets par pixel
        game->draw.color = *(int *)(game->img_data[0].data + index);
    }
    return (0);
}

static void	draw_sky_floor(game_s *game, int column_index, int wall_top, int wall_bottom)
{
    int y;

    y = 0;
    if (wall_top < WIN_H)
    {
        while (y < wall_top)
        {
            mlx_pixel_put(MLX_PTR, WIN_PTR, column_index, y, \
                                        game->draw.ceiling_c);
            y++;
        }
    }
    y = 0;
    if (wall_bottom > 0)
    {
        y = wall_bottom;
        while(y < WIN_H)
        {
            mlx_pixel_put(MLX_PTR, WIN_PTR, column_index, y, \
                                            game->draw.floor_c);
            y++;
        }
    }
}

static void	init_draw(game_s *game, double w_dist, ray_s *ray, int *end_x_y)
{
	static const int	mid_win = WIN_H * 0.5;

    if (w_dist <= 0)
            game->draw.wall_h = WIN_H;
    else
        game->draw.wall_h = (int) WIN_H / w_dist;
    game->draw.wall_t = floor((mid_win) - (game->draw.wall_h * 0.5));
    game->draw.wall_b = floor((mid_win) + (game->draw.wall_h * 0.5));
	if (ray->colision_side == 1)
    {
        if (ray->dir_y < 0) // south
    	    game->draw.txtr_x = (int) end_x_y[1] % game->img_data[1].width;
        else // north
    	    game->draw.txtr_x = (int) end_x_y[1] % game->img_data[0].width;
    }
	else
    {
        if (ray->dir_x < 0) // west
		    game->draw.txtr_x = (int) end_x_y[0] % game->img_data[2].width;
        else // east
		    game->draw.txtr_x = (int) end_x_y[0] % game->img_data[3].width;
    }
    game->draw.i = game->draw.wall_t;
}

void	draw_wall_no_so(game_s *game, ray_s *ray, int col_index, int *end_x_y)
{
    int txtr_y;
    int index;

    init_draw(game, ray->wall_dist, ray, end_x_y);
    while (game->draw.i < game->draw.wall_b)
    {
        if (game->draw.i >= 0 && game->draw.i < WIN_H)
        {
            get_color(game, ray, 0, 0);
			mlx_pixel_put(game->console.mlx_ptr, game->console.win_ptr, \
                                col_index, game->draw.i, game->draw.color);
        }
        game->draw.i++;
    }
    draw_sky_floor(game, col_index, game->draw.wall_t, game->draw.wall_b);
}

void	draw_wall_ea_we(game_s *game, ray_s *ray, int col_index, int *end_x_y)
{
	int	txtr_y;
    int index;

	init_draw(game, ray->wall_dist, ray, end_x_y);
    while (game->draw.i < game->draw.wall_b)
    {
        if (game->draw.i >= 0 && game->draw.i < WIN_H)
        {
            get_color(game, ray, 0, 0);
            mlx_pixel_put(game->console.mlx_ptr, game->console.win_ptr, \
                                col_index, game->draw.i, game->draw.color);
        }
        game->draw.i++;
    }
    draw_sky_floor(game, col_index, game->draw.wall_t, game->draw.wall_b);
}