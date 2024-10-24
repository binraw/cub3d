#include "../headers/cub.h"

int rotate(game_s *game)
{
    if (game->plyr_data.rotate_l || game->plyr_data.rotate_r)
    {
        printf("valeur orientation avant : %f\n", game->plyr_data.orientation);
        
        if (game->plyr_data.rotate_l)
            game->plyr_data.orientation -= ROT_SPEED; // Tourner à gauche
        if (game->plyr_data.rotate_r)
            game->plyr_data.orientation += ROT_SPEED; // Tourner à droite

        printf("valeur orientation apres : %f\n", game->plyr_data.orientation);
        // if (game->plyr_data.orientation < 0)
        //     game->plyr_data.orientation += 2 * M_PI;
        // if (game->plyr_data.orientation >= 2 * M_PI)
        //     game->plyr_data.orientation -= 2 * M_PI;

        //  la direction
        game->plyr_data.dir_x = cos(game->plyr_data.orientation);
        game->plyr_data.dir_y = sin(game->plyr_data.orientation);

        return (1);
    }

    return (0);
}

/*
	* si la prochaine case n'est pas un mur, met a jour les valeurs pos_x et pos_y
	* avec les nouvelles valeurs move_x et move_y
*/
int	move(game_s *game , double move_x, double move_y)
{
	if (move_x < 0 || move_x >= game->map_data.width || 
		move_y < 0 || move_y >= game->map_data.heigth || 
		game->map_data.map[(int) round(move_y)][(int) round(move_x)] == '1')
	{
        // if (game->plyr_data.move_up || game->plyr_data.move_down || \
        // game->plyr_data.move_left || game->plyr_data.move_right || \
        // game->plyr_data.rotate_l || game->plyr_data.rotate_r)
        // {
    	//     game->plyr_data.pos_x = move_x;
	    //     game->plyr_data.pos_y = move_y;

        //     return (0);
        // }
        printf("HIT WALL\n");
		return (1);
	}
	game->plyr_data.pos_x = move_x;
	game->plyr_data.pos_y = move_y;
	return (0);
}
/*
	* increment / decrement l'angle du player de la vitesse de rotation
	* a voir si on doit revenir a l'angle de depart lorsqu'on arrive a 360 degres
*/
void    rotate_player(game_s *game)
{
    if (game->plyr_data.rotate_l)
        game->plyr_data.angle -= ROT_SPEED;
    if (game->plyr_data.rotate_r)
        game->plyr_data.angle += ROT_SPEED;
    game->plyr_data.dir_x = cos(game->plyr_data.angle);
    game->plyr_data.dir_y = sin(game->plyr_data.angle);
}

/*
    * update la position du player
        - stock la valeur des mouvements de translation dans des variables
        - la valeur des variables est validee dans la fonction move() qui update les variables de
        - la structure si move_x et move_y sont valide (ne sortent pas de la map)
        - update de l'angle de rotation dans rotate_player()
*/
int update_movement(game_s *game)
{
	double move_x;
	double move_y;


    move_x = game->plyr_data.pos_x;
    move_y = game->plyr_data.pos_y;
    if (game->plyr_data.move_up)
        move_y -= MOV_SPEED;
    if (game->plyr_data.move_down)
        move_y += MOV_SPEED;
    if (game->plyr_data.move_left)
        move_x -= MOV_SPEED;
    if (game->plyr_data.move_right)
        move_x += MOV_SPEED;
    if (game->plyr_data.rotate_l || game->plyr_data.rotate_r)
        rotate_player(game);
    // if (move_x == 0 && move_y == 0 && rotate(game) == 0)
    // {
    //     // printf("rentre si pas de mouvement\n");
    //     return (1); 
    // }
    return (move(game, move_x, move_y));
}

int loop_hook(game_s *game)
{
    if (game->plyr_data.move_up || game->plyr_data.move_down || \
        game->plyr_data.move_left || game->plyr_data.move_right || \
        game->plyr_data.rotate_l || game->plyr_data.rotate_r)
    {
        printf("before move :\n");
        print_player(game);
        if (update_movement(game) == 1)
		{
			printf("HERE\n");
            return (0);
		}
        printf("after move :\n");
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
