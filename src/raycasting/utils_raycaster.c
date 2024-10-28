#include "cub.h"



int move(game_s *game, double move_x, double move_y)
{
    int new_x = (int)floor(move_x);
    int new_y = (int)floor(move_y);

    if (new_x < 0 || new_x >= game->map_data.width ||
        new_y < 0 || new_y >= game->map_data.heigth ||
        game->map_data.map[new_y][new_x] == '1')
    {
        return (1); // Collision
    }

    game->plyr_data.pos_x = move_x;
    game->plyr_data.pos_y = move_y;
    return (0); // Pas de collision
}



void rotate_player(game_s *game)
{
    if (game->plyr_data.rotate_l)
    {
        game->plyr_data.angle -= ROT_SPEED;
    }
    if (game->plyr_data.rotate_r)
    {
        game->plyr_data.angle += ROT_SPEED;
    }

    // l'angle reste entre 0 et 360 degrés
    game->plyr_data.angle = fmod(game->plyr_data.angle + 360, 360);

    game->plyr_data.dir_x = cos(game->plyr_data.angle * (M_PI / 180)); // Conversion en radians
    game->plyr_data.dir_y = sin(game->plyr_data.angle * (M_PI / 180)); // Conversion en radians
    //printf("valeur des directions : x et y : %f\n %f\n", game->plyr_data.dir_x, game->plyr_data.dir_y);

}


int update_movement(game_s *game)
{
    double move_x = game->plyr_data.pos_x;
    double move_y = game->plyr_data.pos_y;
   // printf("valeur de move_x et move_y : %f\n %f\n", move_x, move_y);
    if (game->plyr_data.move_up)
    {
        move_x += game->plyr_data.dir_x * MOV_SPEED; 
        move_y += game->plyr_data.dir_y * MOV_SPEED; 
    }
    if (game->plyr_data.move_down)
    {
        move_x -= game->plyr_data.dir_x * MOV_SPEED;
        move_y -= game->plyr_data.dir_y * MOV_SPEED; 
    }
    if (game->plyr_data.move_left)
    {
        move_x -= game->plyr_data.dir_y * MOV_SPEED; 
        move_y += game->plyr_data.dir_x * MOV_SPEED; 
    }
    if (game->plyr_data.move_right)
    {
        move_x += game->plyr_data.dir_y * MOV_SPEED;
        move_y -= game->plyr_data.dir_x * MOV_SPEED; 
    }
    if (game->plyr_data.rotate_l || game->plyr_data.rotate_r)
        rotate_player(game);
    
    return move(game, move_x, move_y);
}

int loop_hook(game_s *game)
{
    if (game->plyr_data.move_up || game->plyr_data.move_down || \
        game->plyr_data.move_left || game->plyr_data.move_right || \
        game->plyr_data.rotate_l || game->plyr_data.rotate_r)
    {

        print_player(game);
        if (update_movement(game) == 1)
		{
            return (0);
		}
        print_player(game);
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