#include "cub.h"

int get_texture_color(void *img_ptr, int x, int y, int texture_width)
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

void    draw_sky(game_s *game, int column_index, int wall_top)
{
    int y;
    int sky_color;

    // printf("rentre dans sky\n");
    y = 0;
    // printf("valeur tex_c : %d\n", game->texture.c_color[0]);
    sky_color = (game->texture.c_color[0] << 16) | (game->texture.c_color[1] << 8) | game->texture.c_color[2];
    // printf("valeur sky_color : %d\n", sky_color);
    // printf("y = %d : wall top == %d\n", y, wall_top);
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

void    draw_floor(game_s *game, int column_index, int wall_bottom)
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
// x doit etre le point x ou le rayon touche le mur et pareil pour le y

void draw_wall_no(game_s *game, ray_s *ray, int column_index, int *end_x_y)
{
    int wall_height;
    int wall_top;
    int wall_bottom;
    int y;
    int texture_x;
    int color;
    int texture_y;

    if (ray->wall_dist < 0)
        wall_height = WIN_H;
    else
        wall_height = floor(WIN_H / ray->wall_dist);
    wall_top = floor((WIN_H / 2) - (wall_height / 2));
    wall_bottom = floor((WIN_H / 2) + (wall_height / 2));

    // Calcul de texture_x en fonction de l'orientation du mur
    texture_x = (int) end_x_y[0] % game->img_data.width[0];

    y = wall_top;
    while (y < wall_bottom)
    {
        if (y >= 0 && y < WIN_H)
        {
            texture_y = ((y - wall_top) * game->img_data.height[0]) / wall_height;
            color = get_texture_color(game->img_data.img_text_no, texture_x, texture_y, game->img_data.width[0]);
            // printf("valeur de la color : %d\n", color);
            mlx_pixel_put(game->console.mlx_ptr, game->console.win_ptr, column_index, y, color);
        }
        y++;
    }
    draw_sky(game, column_index, wall_top);
    draw_floor(game, column_index, wall_bottom);
}

void draw_wall_so(game_s *game, ray_s *ray, int column_index, int *end_x_y)
{
    int wall_height;
    if (ray->wall_dist <= 0)
        wall_height = WIN_H;
    else
        wall_height = floor(WIN_H / ray->wall_dist);
    const int	wall_top = floor((WIN_H / 2) - (wall_height / 2));
    const int	wall_bottom = floor((WIN_H / 2) + (wall_height / 2));
    int			texture_x;
    int			texture_y;
    int			color;
    int			y;

    texture_x = (int) end_x_y[0] % game->img_data.width[1];
    y = wall_top;
    while (y < wall_bottom)
    {
        if (y >= 0 && y < WIN_H)
        {
            texture_y = ((y - wall_top) * game->img_data.height[1]) / wall_height;
            color = get_texture_color(game->img_data.img_text_so, texture_x, texture_y, game->img_data.width[1]);

            mlx_pixel_put(game->console.mlx_ptr, game->console.win_ptr, column_index, y, color);
        }
        y++;
    }
    draw_sky(game, column_index, wall_top);
    draw_floor(game, column_index, wall_bottom);
}

void draw_wall_we(game_s *game, ray_s *ray, int column_index, int *end_x_y)
{
    int wall_height;
    int wall_top;
    int wall_bottom;
    int y;
    int texture_x;
    int color;
    int texture_y;

    if (ray->wall_dist <= 0)
        wall_height = WIN_H;
    else
        wall_height = floor(WIN_H / ray->wall_dist);
    wall_top = floor((WIN_H / 2) - (wall_height / 2));
    wall_bottom = floor((WIN_H / 2) + (wall_height / 2));
    texture_x = (int) end_x_y[1] % game->img_data.width[2];
    y = wall_top;
    while (y < wall_bottom)
    {
        if (y >= 0 && y < WIN_H)
        {
            texture_y = ((y - wall_top) * game->img_data.height[2]) / wall_height;
            color = get_texture_color(game->img_data.img_text_we, texture_x, texture_y, game->img_data.width[2]);

            mlx_pixel_put(game->console.mlx_ptr, game->console.win_ptr, column_index, y, color);
        }
        y++;
    }
    draw_sky(game, column_index, wall_top);
    draw_floor(game, column_index, wall_bottom);
}

void draw_wall_ea(game_s *game, ray_s *ray, int column_index, int *end_x_y)
{
    int wall_height;
    int wall_top;
    int wall_bottom;
    int y;
    int texture_x;
    int color;
    int texture_y;

    if (ray->wall_dist <= 0)
        wall_height = WIN_H;
    else
        wall_height = floor(WIN_H / ray->wall_dist);
    wall_top = floor((WIN_H / 2) - (wall_height / 2));
    wall_bottom = floor((WIN_H / 2) + (wall_height / 2));
    texture_x = (int) end_x_y[1] % game->img_data.width[3];
    y = wall_top;
    while (y < wall_bottom)
    {
        if (y >= 0 && y < WIN_H)
        {
            texture_y = ((y - wall_top) * game->img_data.height[3]) / wall_height;
            color = get_texture_color(game->img_data.img_text_ea, texture_x, texture_y, game->img_data.width[3]);

            mlx_pixel_put(game->console.mlx_ptr, game->console.win_ptr, column_index, y, color);
        }
        y++;
    }
    draw_sky(game, column_index, wall_top);
    draw_floor(game, column_index, wall_bottom);
}



void draw_wall_all(game_s *game, ray_s *ray, int i, int *end_x_y)
{
    // print_ray(ray);
    if (ray->colision_side == 1)
    {
        if (ray->dir_x < 0)
        {
            draw_wall_we(game, ray, i, end_x_y); // Ouest
        }
        else
        {
            draw_wall_ea(game, ray, i, end_x_y); // Est
        }
    }
    else
    {
        if (ray->dir_y < 0)
        {
            draw_wall_so(game, ray, i, end_x_y); // Sud
        }
        else
        {
            draw_wall_no(game, ray, i, end_x_y); // Nord
        }
    }
}
