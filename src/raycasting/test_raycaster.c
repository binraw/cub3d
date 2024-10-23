#include "../headers/cub.h"


// init des donnes utils dans ray
void init_ray(ray_s *ray, game_s *game, int pixel_column)
{
    double camera_x;

    camera_x = 2 * pixel_column / (double)WIN_W - 1;
    ray->pos_x = game->plyr_data.pos_x;
    ray->pos_y = game->plyr_data.pos_y;
    ray->dir_x = game->plyr_data.dir_x + game->plyr_data.plane_x * camera_x;
    ray->dir_y = game->plyr_data.dir_y + game->plyr_data.plane_y * camera_x;
    ray->map_x = (int)ray->pos_x;
    ray->map_y = (int)ray->pos_y;
    ray->delta_dist_x = fabs(1 / ray->dir_x);
    ray->delta_dist_y = fabs(1 / ray->dir_y);
    ray->hit = 0;
}

// algo dda pour determiner si un mur est toucher
void dda(game_s *game, ray_s *ray)
{
    if (ray->dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
    }
    if (ray->dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
    }
    while (!ray->hit)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        if (game->map[ray->map_x][ray->map_y] == '1')
            ray->hit = 1;
    }
}


// fct draw modifier pour fonctionner avec le nouveau systeme dda 
void draw_wall(game_s *game, int column_index, ray_s *ray)
{
    int wall_height;
    int wall_top;
    int wall_bottom;
    int wall_color;
    int y;

    wall_height = (int)(WIN_H / ray->wall_dist);
    wall_top = (WIN_H / 2) - (wall_height / 2);
    wall_bottom = (WIN_H / 2) + (wall_height / 2);
    wall_color = 0xFFFFFF;
    y = wall_top;
    while (y < wall_bottom)
    {
        if (y >= 0 && y < WIN_H) 
        { 
            mlx_pixel_put(MLX_PTR, WIN_PTR, column_index, y, wall_color);
        }
        y++;
    }
    y = 0;
    while (y < wall_top)
    {
        if (y >= 0 && y < WIN_H)
        {
            mlx_pixel_put(MLX_PTR, WIN_PTR, column_index, y, 0x00BFFF); // Bleu clair pour le plafond
        }
        y++;
    }
    y = wall_bottom;
    while (y < WIN_H)
    {
        if (y >= 0 && y < WIN_H)
        {
            mlx_pixel_put(MLX_PTR, WIN_PTR, column_index, y, 0x8B4513); // Marron pour le sol
        }
        y++;
    }
}

// boucle raycaster pour chaque rayon 
int compute_ray(game_s *game)
{
    ray_s ray;
    int i;

    i = 0;
    while (i < WIN_W)
    {
        init_ray(&ray, game, i);
        dda(game, &ray);
        draw_wall(game, &ray, i);
        i++;
    }
    return (0);
}
