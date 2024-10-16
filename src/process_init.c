#include "../headers/cub.h"


int process_create_map(game_s *game, char *file)
{
    int y;
    printf("rentre dans le create map\n");
    read_file(file, game);
    y = init_all_texture(game);

    printf("valeur de y :%d\n", y);
    if (y == -1) // gerer ici les free etc ..
        exit(1);
    y++;
    init_pixel_map(game, y);
    if (isclosed(game) == 0) // gerer ici les free etc ..
        exit(1);
     //if (isclosed_column(game, y) == 0) // reussir a faire fonctionner la fct qui permet de check 
       // exit(1);
    // en colonne si c'est bien 1 le dernier et pas un 0
    
    if (init_pos_player(game, y) == -1) // gerer ici les free etc ..
        exit(1);
    printf("Map valide bravo \n");
    return (0);
}

int init_pixel_map(game_s *game, int y)
{
    printf("rentre bien dans init\n");
    game->num_line_map = 0;
    printf("%d\n", game->numb_line);
    game->num_line_map = game->numb_line - y;
    game->map = dup_map_pixel(game, y);
	if (!game->map)
        return (-1);
    return (0);
}


int init_pos_player(game_s *game, int x)
{
    player_s player;
    //size_t i;
    int y;

   // i = 0;
    y = x;
    while(game->map[y] && y < game->numb_line)
    {
        if (control_value_player(&player, game->map[y]) == -1)
            return (-1);
        y++;
    }
    return (0);
}

int    control_value_player(player_s *player, char *str)
{
    int result;

    result = 0;
    if (ft_strchr(str, 'N') && ft_strchr(str, 'O'))
        player->player_no = 1;
    if (ft_strchr(str, 'S') && ft_strchr(str, 'O'))
        player->player_so = 1;
    if (ft_strchr(str, 'W') && ft_strchr(str, 'E'))
        player->player_we = 1;
    if (ft_strchr(str, 'E') && ft_strchr(str, 'A'))
        player->player_ea = 1;
    result += player->player_ea + player->player_no + player->player_so + player->player_we;
    if (result > 1) //test pour voir si plusieur player sur la carte
        return (-1);
    return (0);
}



// je pense check d'abord toutes les lignes 
// et ensuite toutes les colonnes
// int isclosed(game_s *game, int x)
// {
//     size_t i;
//     size_t y;
//     int value_x;
//     int value_y;

//     i = 0;
//     y = x;
//     value_x = 1; //init a 1 pour eviter de return trop tot
//     value_y = 1;
//     while (game->map[y] && y < game->numb_line)
//     {
//         i = 0;
//         while(game->map[y][i] && game->map[y][i] == '\n')
//             y++;
//         printf("value de la premiere lign a check : %s\n", game->map[y]);
//         while(game->map[y][i] && game->map[y][i] == ' ') //ici un check que le premier n'est pas un 0
//             i++;
//         if (check_last_value(game, y, i) == 0)
//             return (0);
//         while (game->map[y][i])
//         {
//             value_x = check_last_value(game, y, i);//ici un check que le dernier n'est pas un 0
//             printf("value de la premiere lign a check : %c\n", game->map[y][i]);
//             i++;  
//         }
//         printf("fin de ligne \n");
//         if (value_x == 0)
//             return (0);
//         y++;
//     }
//     return (1);
// }

int isclosed(game_s *game)
{
    int i;
   	int  y;
    int value_x;
    //int value_y;

    i = 0;
    y = 0;
    value_x = 1; //init a 1 pour eviter de return trop tot
    //value_y = 1;
    while (game->map[y] && y < game->num_line_map)
    {
        i = 0;
        while(game->map[y][i] && game->map[y][i] == '\n')
            y++;
        printf("value de la premiere lign a check : %s\n", game->map[y]);
        while(game->map[y][i] && game->map[y][i] == ' ') //ici un check que le premier n'est pas un 0
            i++;
        if (check_last_value(game, y, i) == 0)
            return (0);
        while (game->map[y][i])
        {
            value_x = check_last_value(game, y, i);//ici un check que le dernier n'est pas un 0
            printf("value de la premiere lign a check : %c\n", game->map[y][i]);
            i++;  
        }
        printf("fin de ligne \n");
        if (value_x == 0)
            return (0);
        y++;
    }
    return (1);
}


int isclosed_column(game_s *game)
{
    int i;
    int y;
   // int value_x;
    int value_y;

    i = 0;
    y = 0;
   // value_x = 1; //init a 1 pour eviter de return trop tot
    value_y = 1;
    while (game->map[y][i])
    {
        y = 0;
        while(game->map[y][i] && game->map[y][i] == '\n')
            y++;
        printf("value de la premiere lign a check : %s\n", game->map[y]);
        while(game->map[y][i] && game->map[y][i] == ' ')
            y++;
        if (game->map[y][i] && game->map[y][i] == '0') // ici check premier de la colonne
            return (0);
        while (game->map[y] && y < game->numb_line)
        {
            printf("boucle \n");
            value_y = check_last_value(game, y, i); // ici garde la valeur du dernier de la colonne
            y++;
        }
        if (value_y == 0)
            return (0);
        i++;
    }
    return (1);
}

int check_last_value(game_s *game, int y, size_t i)
{
    if (game->map[y][i] == '1')
        return (1);
    else if (game->map[y][i] == '0')
        return (0);
    else
        return (1);
}
