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
        game->plyr_data.dir_x = cos(game->plyr_data.orientation);
        game->plyr_data.dir_y = sin(game->plyr_data.orientation);

        return (1);
    }

    return (0);
}

//on donne les valeur a ajouter a notre position et on check si la nouvelle position n'est pas un mur

int	move(game_s *game , double move_x, double move_y)
{
	double	new_pos_x;
	double	new_pos_y;

	// new_pos_x = game->plyr_data.pos_x + move_x  * MOV_SPEED;
	// new_pos_y = game->plyr_data.pos_y + move_y * MOV_SPEED;
    	new_pos_x = game->plyr_data.pos_x + move_x;
	new_pos_y = game->plyr_data.pos_y + move_y;
	if (new_pos_x < 0 || new_pos_x >= game->map_data.width || 
		new_pos_y < 0 || new_pos_y >= game->map_data.heigth || 
		game->map_data.map[(int)new_pos_y][(int)new_pos_x] == '1')
	{
        printf("on rentre la\n");
		return (1);
	}
    // printf(" OLD game->plyr_data.pos_x : %f\n", game->plyr_data.pos_x);
	game->plyr_data.pos_x = new_pos_x;
	game->plyr_data.pos_y = new_pos_y;
    // printf("game->plyr_data.pos_x : %f\n", game->plyr_data.pos_x);
	return (0);
}




int update_movement(game_s *game)
{
	double move_x;
	double move_y;


    move_x = 0;
    move_y = 0;
    //utilisation de la ou le player regarde pour avancer dasn la bonne direction
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
        // Pour aller a gauche on utilise la direction perpendiculaire
        move_x -= game->plyr_data.dir_y * MOV_SPEED;
        move_y += game->plyr_data.dir_x * MOV_SPEED;
    }
    if (game->plyr_data.move_right)
    {
        // Pareil pour la droite de l'autre coter
        move_x += game->plyr_data.dir_y * MOV_SPEED;
        move_y -= game->plyr_data.dir_x * MOV_SPEED;
    }

    //     if (game->plyr_data.move_up)
    // {
    //     move_x +=  MOV_SPEED; 
    //     move_y +=  MOV_SPEED;
    // }
    // if (game->plyr_data.move_down)
    // {
    //     move_x -=  MOV_SPEED;
    //     move_y -=  MOV_SPEED;
    // }
    // if (game->plyr_data.move_left)
    // {
    //     // Pour aller a gauche on utilise la direction perpendiculaire
    //     move_x -=  MOV_SPEED;
    //     move_y +=  MOV_SPEED;
    // }
    // if (game->plyr_data.move_right)
    // {
    //     // Pareil pour la droite de l'autre coter
    //     move_x +=  MOV_SPEED;
    //     move_y -=  MOV_SPEED;
    // }
    if (move_x == 0 && move_y == 0 && rotate(game) == 0)
    {
        // printf("rentre si pas de mouvement\n");
        return (1); 
    }
	move(game, move_x, move_y);
    return (0);
}

int loop_hook(game_s *game)
{
    
    if (update_movement(game) == 1)
        return (0);
    raycaster(game);
    // printf("value de la pos x : %f\n", game->plyr_data.pos_x);
    // printf("BOUGE \n");
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
