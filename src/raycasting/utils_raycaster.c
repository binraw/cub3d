#include "cub.h"

int move(game_s *game, double move_x, double move_y)
{
    int		map_grid_y;
	int		map_grid_x;
	double	new_x;
	double	new_y;

    new_x = game->plyr_data.pos_x + move_x;
	new_y = game->plyr_data.pos_y + move_y;
	map_grid_x = (int) floor((double)new_x / TILE_S);
	map_grid_y = (int) floor((double)new_y / TILE_S);
	if (game->map_data.map[map_grid_y][map_grid_x] != '1' && game->map_data.map[map_grid_y][map_grid_x] != ' ')
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
    if (game->plyr_data.rotate_l || game->plyr_data.rotate_r)
        rotate_player(game);
    else if (game->plyr_data.move_up)
        return (move(game, cos(game->plyr_data.angle) * MOV_SPEED, \
                            sin(game->plyr_data.angle) * MOV_SPEED));
    else if (game->plyr_data.move_down)
        return (move(game, -cos(game->plyr_data.angle) * MOV_SPEED, \
                            -sin(game->plyr_data.angle) * MOV_SPEED));
    else if (game->plyr_data.move_left)
        return (move(game, sin(game->plyr_data.angle) * MOV_SPEED, \
                            -cos(game->plyr_data.angle) * MOV_SPEED));
    else if (game->plyr_data.move_right)
        return (move(game, -sin(game->plyr_data.angle) * MOV_SPEED, \
                            cos(game->plyr_data.angle) * MOV_SPEED));
    return (0);
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
