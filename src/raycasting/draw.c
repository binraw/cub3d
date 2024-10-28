#include "cub.h"

int get_texture_color(void *img_ptr, int x, int y, int texture_width)
{
    char *data;
    int bpp; // bits par pixel
    int size_line; // taille de chaque ligne
    int endian; // ordre de stockage
    int color;

    // Obtenir les données de l'image
    data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);

    // Calculer l'index du pixel
    int index = (y * size_line + x * (bpp / 8)); // bpp / 8 pour obtenir le nombre d'octets par pixel

    // Récupérer la couleur du pixel
    color = *(int *)(data + index); // Cast pour obtenir la couleur

    return color;
}

// x doit etre le point x ou le rayon touche le mur et pareil pour le y



void draw_wall_no(game_s *game, ray_s *ray, int column_index, double distance)
{
    int wall_height;
    int wall_top;
    int wall_bottom;
    int y;
    int texture_x;

    wall_height = (int)(WIN_H / distance);
    wall_top = (WIN_H / 2) - (wall_height / 2);
    wall_bottom = (WIN_H / 2) + (wall_height / 2);
    
    // Calcul de texture_x en fonction de l'orientation du mur
    texture_x = (int)(ray->pos_y * game->img_data.height[0]) % game->img_data.width[0];

    y = wall_top;
    while (y < wall_bottom)
    {
        if (y >= 0 && y < WIN_H)
        {
            int texture_y = ((y - wall_top) * game->texture_height[0]) / wall_height; // Coordonnée y dans la texture
            int color = get_texture_color(game->img_data.img_text_no, texture_x, texture_y, game->img_data.width[0]);

            mlx_pixel_put(game->conole.mlx_ptr, game->console.win_ptr, column_index, y, color);
        }
        y++;
    }

    // afficher le sol et le ciel apres
}
