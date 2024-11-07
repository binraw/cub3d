

#include "cub.h"

static inline int utils_color(game_s *game, ray_s *ray, int nb, int *end_x_y)
{
    int txtr_y;
    int txtr_x;
    int index;

    // Calcul de txtr_x basé sur la position d'impact du rayon, avec partie décimale seulement
    if (ray->colision_side == 1)  // Si la collision est sur un mur vertical
    {
        float wall_hit_y = (game->plyr_data.pos_y / TILE_S) + ray->wall_dist * ray->dir_y;
        wall_hit_y -= floor(wall_hit_y);  // Garder uniquement la partie décimale pour l'alignement de la texture
        txtr_x = (int)(wall_hit_y * game->img_data[nb].width);
    }
    else  // Si la collision est sur un mur horizontal
    {
        float wall_hit_x = (game->plyr_data.pos_x / TILE_S) + ray->wall_dist * ray->dir_x;
        wall_hit_x -= floor(wall_hit_x);  // Garder uniquement la partie décimale
        txtr_x = (int)(wall_hit_x * game->img_data[nb].width);
    }

    // Calcul de txtr_y basé sur la hauteur projetée du mur
    txtr_y = ((game->draw.i - game->draw.wall_t) * game->img_data[nb].height) / game->draw.wall_h;

    // Vérification des bornes de l'index pour éviter tout dépassement de mémoire
    index = (txtr_y * game->img_data[nb].s_line + txtr_x * (game->img_data[nb].bpp / 8));
    if (index < 0)
        index = 0;
    if (index >= game->img_data[nb].s_line * game->img_data[nb].height)
        index = game->img_data[nb].s_line * game->img_data[nb].height - 1;

    int color = *(int*)(game->img_data[nb].data + index);
    return color;
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
