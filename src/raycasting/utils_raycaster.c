#include "cub.h"

int move(game_s *game, double move_x, double move_y)
{
    double		map_grid_y;
	double		map_grid_x;
	double		new_x;
	double		new_y;

    // printf("BEFORE : move_x == %f : move_y == %f\ngame->plyr_data.pos_x == %f : game->plyr_data.pos_y == %f\n", move_x, move_y, game->plyr_data.pos_x, game->plyr_data.pos_y);
    new_x = game->plyr_data.pos_x + move_x;
	new_y = game->plyr_data.pos_y + move_y;
    // printf("AFTER : new_x == %f : new_y == %f\n", new_x, new_y);
	map_grid_x = round((double)new_x / TILE_S);
	map_grid_y = round((double)new_y / TILE_S);
    // printf("grid_x == %f : grid_y == %f\n\n\n", map_grid_x, map_grid_y);
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
        game->plyr_data.angle -= ROT_SPEED;
    if (game->plyr_data.rotate_r)
        game->plyr_data.angle += ROT_SPEED;
    if (game->plyr_data.angle < 0)
        game->plyr_data.angle += M_PI * 2;
    if (game->plyr_data.angle > M_PI * 2)
        game->plyr_data.angle -= M_PI * 2;
    game->plyr_data.dir_x = cos(game->plyr_data.angle);
    game->plyr_data.dir_y = sin(game->plyr_data.angle);
}

int update_movement(game_s *game)
{
    double move_x;
    double move_y;

    if (game->plyr_data.move_up)
    {
        // if (game->plyr_data.pos_y > 0 + TILE_S)
        //     game->plyr_data.pos_y -= (double) MOV_SPEED;
        move_x = cos(game->plyr_data.angle) * MOV_SPEED;
        move_y = sin(game->plyr_data.angle) * MOV_SPEED;
    }
    if (game->plyr_data.move_down)
    {
        // if (game->plyr_data.pos_y < game->map_data.heigth * TILE_S)
        //     game->plyr_data.pos_y += (double) MOV_SPEED;
        move_x = -cos(game->plyr_data.angle) * MOV_SPEED;
        move_y = -sin(game->plyr_data.angle) * MOV_SPEED;
    }
    if (game->plyr_data.move_left)
    {
        // if (game->plyr_data.pos_x > 0 + TILE_S)
        //     game->plyr_data.pos_x -= (double) MOV_SPEED;
        move_x = sin(game->plyr_data.angle) * MOV_SPEED;
        move_y = -cos(game->plyr_data.angle) * MOV_SPEED;
    }
    if (game->plyr_data.move_right)
    {
        // if (game->plyr_data.pos_x < game->map_data.width * TILE_S)
        //     game->plyr_data.pos_x += (double) MOV_SPEED;
        move_x = -sin(game->plyr_data.angle) * MOV_SPEED;
        move_y = cos(game->plyr_data.angle) * MOV_SPEED;
    }
    if (game->plyr_data.rotate_l || game->plyr_data.rotate_r)
        rotate_player(game);
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
