#include "../headers/cub.h"

int	rotate(game_s *game)
{
	double	old_x;

	old_x = game->plyr_data.pos_x;
	game->plyr_data.pos_x = old_x * cos(game->plyr_data.angle) - game->plyr_data.pos_y * sin(game->plyr_data.angle);
	game->plyr_data.pos_y = old_x * sin(game->plyr_data.angle) + game->plyr_data.pos_y * cos(game->plyr_data.angle);
	return (0);
}

//on donne les valeur a ajouter a notre position et on check si la nouvelle position n'est pas un mur

int	move(game_s *game , double move_x, double move_y)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = game->plyr_data.pos_x + move_x  * MOV_SPEED;
	new_pos_y = game->plyr_data.pos_y + move_y * MOV_SPEED;
	if (new_pos_x < 0 || new_pos_x >= game->map_data.width || 
		new_pos_y < 0 || new_pos_y >= game->map_data.heigth || 
		game->map_data.map[(int)new_pos_y][(int)new_pos_x] == '1')
	{
		return (1);
	}
	game->plyr_data.pos_x = new_pos_x;
	game->plyr_data.pos_y = new_pos_y;
	return (0);
}




int update_movement(game_s *game)
{
	double move_x;
	double move_y;


    move_x = 0;
    move_y = 0;
    if (game->plyr_data.move_up)
    {
        move_x += cos(game->plyr_data.angle);
        move_y += sin(game->plyr_data.angle);
    }
    if (game->plyr_data.move_down)
    {
        move_x -= cos(game->plyr_data.angle);
        move_y -= sin(game->plyr_data.angle);
    }
    if (game->plyr_data.move_left)
    {
        move_x -= sin(game->plyr_data.angle);
        move_y += cos(game->plyr_data.angle);
    }
    if (game->plyr_data.move_right)
    {
        move_x += sin(game->plyr_data.angle);
        move_y -= cos(game->plyr_data.angle);
    }
    // double length = sqrt(move_x * move_x + move_y * move_y); //ralenti si le deplacement va trop vite
    // if (length > 1)
    // {
    //     move_x /= length;
    //     move_y /= length;
    // }
    if (move_x == 0 && move_y == 0)
        return (1);
	move(game, move_x, move_y);
    return (0);
}

int loop_hook(game_s *game)
{
    if (update_movement(game) == 1)
        return (0);
    rotate(game);
   
    raycaster(game);
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
