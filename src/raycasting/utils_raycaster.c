#include "cub.h"

int move(game_s *game, double move_x, double move_y)
{
    // int new_x = roundf(move_x + game->plyr_data.pos_x);
    // int new_y = roundf(move_y + game->plyr_data.pos_y);

    // if (new_x < 0 || new_x >= game->map_data.width ||
    //     new_y < 0 || new_y >= game->map_data.heigth ||
    //     game->map_data.map[new_y][new_x] == '1')
    // {

    //     return (1); // Collision
    // }

    // game->plyr_data.pos_x = new_x;
    // game->plyr_data.pos_y = new_y;
    // return (0); // Pas de collision
    double		map_grid_y;
	double		map_grid_x;
	double		new_x;
	double		new_y;

    printf("BEFORE : move_x == %f : move_y == %f\ngame->plyr_data.pos_x == %f : game->plyr_data.pos_y == %f\n", move_x, move_y, game->plyr_data.pos_x, game->plyr_data.pos_y);
    new_x = game->plyr_data.pos_x + move_x;
	new_y = game->plyr_data.pos_y + move_y;
    printf("AFTER : new_x == %f : new_y == %f\n", new_x, new_y);
	map_grid_x = round((double)new_x / TILE_S);
	map_grid_y = round((double)new_y / TILE_S);
    printf("grid_x == %f : grid_y == %f\n\n\n", map_grid_x, map_grid_y);
	if (game->map_data.map[(int)map_grid_y][(int)map_grid_x] != '1')
	{
		game->plyr_data.pos_x = new_x;
		game->plyr_data.pos_y = new_y;
        return (0);
	}
    return (1);
}

void rotate_player(game_s *game)
{
    if (game->plyr_data.rotate_l)
    {
        game->plyr_data.angle -= ROT_SPEED;
        if (game->plyr_data.angle < 0)
            game->plyr_data.angle += M_PI * 2;
    }
    if (game->plyr_data.rotate_r)
    {
        game->plyr_data.angle += ROT_SPEED;
        if (game->plyr_data.angle > M_PI * 2)
            game->plyr_data.angle -= M_PI * 2;
    }
}

// void update_player_rotation(game_s *game)
// {
//     if (game->plyr_data.rotate_l) {
//         rotate_camera(game, ROT_SPEED); // Tourner à gauche
//     }
//     if (game->plyr_data.rotate_r) {
//         rotate_camera(game, -ROT_SPEED); // Tourner à droite
//     }
// }

// void rotate_camera(game_s *game, float angle)
// {
//     float old_dir_x;
//     float old_plane_x;
//     float rad;
//     old_dir_x = game->plyr_data.dir_x;
//     old_plane_x = game->plyr_data.plane_x;
//     // Conversion de l'angle en radians
//     rad = angle * (M_PI / 180);
//     // Calcul des nouvelles directions
//     game->plyr_data.dir_x = old_dir_x * cos(rad) - game->plyr_data.dir_y * sin(rad);
//     game->plyr_data.dir_y = old_dir_x * sin(rad) + game->plyr_data.dir_y * cos(rad);
//     // Calcul des nouvelles directions du plan
//     game->plyr_data.plane_x = old_plane_x * cos(rad) - game->plyr_data.plane_y * sin(rad);
//     game->plyr_data.plane_y = old_plane_x * sin(rad) + game->plyr_data.plane_y * cos(rad);
// }

int update_movement(game_s *game)
{
    double move_x;
    double move_y;

    if (game->plyr_data.move_up)
    {
        move_x = cos(game->plyr_data.angle) * MOV_SPEED;
        move_y = sin(game->plyr_data.angle) * MOV_SPEED;
    }
    if (game->plyr_data.move_down)
    {
        move_x = -cos(game->plyr_data.angle) * MOV_SPEED;
        move_y = -sin(game->plyr_data.angle) * MOV_SPEED;
    }
    if (game->plyr_data.move_left)
    {
        move_x = sin(game->plyr_data.angle) * MOV_SPEED;
        move_y = -cos(game->plyr_data.angle) * MOV_SPEED;
    }
    if (game->plyr_data.move_right)
    {
        move_x = -sin(game->plyr_data.angle) * MOV_SPEED;
        move_y = -cos(game->plyr_data.angle) * MOV_SPEED;
    }
    if (game->plyr_data.rotate_l || game->plyr_data.rotate_r)
    {
        rotate_player(game);
        return (0);
    }
    return (move(game, move_x, move_y));
}

int loop_hook(game_s *game)
{
    if (game->plyr_data.move_up || game->plyr_data.move_down || \
        game->plyr_data.move_left || game->plyr_data.move_right || \
        game->plyr_data.rotate_l || game->plyr_data.rotate_r)
    {

        if (update_movement(game) == 1)
            return (0);
        raycaster(game);
    }
    return (0);
}

// Si un joueur fait face à un angle de 0 radians (vers la droite), se déplacer à gauche signifie :
// Angle 0 :
// sin(0) = 0 et cos(0) = 1
// Mouvement à gauche : move_x -= 0 (pas de changement) et move_y += 1 (déplacement vers le haut).
// Si le joueur fait face à un angle de 90 degrés (ou π/2 radians, vers le haut), se déplacer à gauche signifie :
// Angle π/2 :
// sin(π/2) = 1 et cos(π/2) = 0
// Mouvement à gauche : move_x -= 1 (déplacement vers la gauche) et move_y += 0 (pas de changement en y).
