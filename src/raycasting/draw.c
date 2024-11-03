#include "cub.h"

static int	get_color(void *img_ptr, int x, int y, int texture_width)
{
    char *data;
    int bpp; // bits par pixel
    int size_line; // taille de chaque ligne
    int endian; // ordre de stockage
    int color;
    int index;

    // printf("rentre dans la recup de texture pour afficher le bon pixel \n");
    // Obtenir les données de l'image
    data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);

    // Calculer l'index du pixel
    index = (y * size_line + x * (bpp / 8)); // bpp / 8 pour obtenir le nombre d'octets par pixel

    // Récupérer la couleur du pixel
    color = *(int *)(data + index); // Cast pour obtenir la couleur

    return color;
}

static void	draw_sky(game_s *game, int column_index, int wall_top)
{
    int y;
    int sky_color;

    y = 0;
    sky_color = (game->texture.c_color[0] << 16) | (game->texture.c_color[1] << 8) | game->texture.c_color[2];
    if (wall_top < WIN_H)
    {
        while (y < wall_top)
        {
            if (y >= 0 && y < WIN_H)
            {
                mlx_pixel_put(MLX_PTR, WIN_PTR, column_index, y, sky_color);
            }
            y++;
        }
    }
}

static void	draw_floor(game_s *game, int column_index, int wall_bottom)
{
    int y;
    int floor_color;

    y = 0;
    floor_color = (game->texture.f_color[0] << 16) | (game->texture.f_color[1] << 8) | game->texture.f_color[2];
    if (wall_bottom > 0)
    {
        y = wall_bottom;
        while(y < WIN_H)
        {
            mlx_pixel_put(MLX_PTR, WIN_PTR, column_index, y, floor_color);
            y++;
        }
    }
}

static void	init_draw(game_s *game, double wall_dist, int colision_side, int *end_x_y)
{
	static const int	mid_win = WIN_H * 0.5;

    if (wall_dist <= 0)
        game->draw.wall_h = WIN_H;
    else
        game->draw.wall_h = floor(WIN_H / wall_dist);
    game->draw.wall_t = floor((mid_win) - (game->draw.wall_h * 0.5));
    game->draw.wall_b = floor((mid_win) + (game->draw.wall_h * 0.5));
	if (colision_side == 1)
    	game->draw.txtr_x = (int) end_x_y[1] % game->img_data.width[3];
	else
		game->draw.txtr_x = (int) end_x_y[0] % game->img_data.width[3];
    game->draw.i = game->draw.wall_t;
}

void	draw_wall_no_so(game_s *game, ray_s *ray, int column_index, int *end_x_y)
{
    int txtr_y;

    init_draw(game, ray->wall_dist, ray->colision_side, end_x_y);
    while (game->draw.i < game->draw.wall_b)
    {
        if (game->draw.i >= 0 && game->draw.i < WIN_H)
        {
            txtr_y = ((game->draw.i - game->draw.wall_t) * game->img_data.height[0]) / game->draw.wall_h;
            if (ray->dir_y < 0)
				game->draw.color = get_color(game->img_data.img_text_so, game->draw.txtr_x, txtr_y, game->img_data.width[0]);
            else
				game->draw.color = get_color(game->img_data.img_text_no, game->draw.txtr_x, txtr_y, game->img_data.width[0]);
				
			mlx_pixel_put(game->console.mlx_ptr, game->console.win_ptr, column_index, game->draw.i, game->draw.color);
        }
        game->draw.i++;
    }
    draw_sky(game, column_index, game->draw.wall_t);
    draw_floor(game, column_index, game->draw.wall_b);
}

void	draw_wall_ea_we(game_s *game, ray_s *ray, int column_index, int *end_x_y)
{
	int	txtr_y;

	init_draw(game, ray->wall_dist, ray->colision_side, end_x_y);
    while (game->draw.i < game->draw.wall_b)
    {
        if (game->draw.i >= 0 && game->draw.i < WIN_H)
        {
			txtr_y = ((game->draw.i - game->draw.wall_t) * \
					game->img_data.height[2]) / game->draw.wall_h;
			if (ray->dir_x < 0)
				game->draw.color = get_color(game->img_data.img_text_we, \
							game->draw.txtr_x, txtr_y, game->img_data.width[3]);
			else
				game->draw.color = get_color(game->img_data.img_text_ea, \
								game->draw.txtr_x, txtr_y, game->img_data.width[3]);
            mlx_pixel_put(game->console.mlx_ptr, game->console.win_ptr, \
								column_index, game->draw.i, game->draw.color);
        }
        game->draw.i++;
    }
    draw_sky(game, column_index, game->draw.wall_t);
    draw_floor(game, column_index, game->draw.wall_b);
}
