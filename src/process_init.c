#include "cub.h"




int init_pos_player(game_s *game, int x)
{
    player_s player;
    size_t i;
    size_t y;

    i = 0;
    y = x;
    // ft_bzero((void*)player, sizeof(player_s));
    while(game->map_data.map[y] && y < game->map_data.width)
    {
        if (control_value_player(&player, game->map_data.map[y]) == -1)
            return (-1);
        y++;
    }
    return (0);
}

int    control_value_player(player_s *player, char *str)
{
    (void) player;
    (void) str;
    // int result;

    // result = 0;
    // if (ft_strchr(str, 'N') && ft_strchr(str, 'O'))
    //     player->player_no = 1;
    // if (ft_strchr(str, 'S') && ft_strchr(str, 'O'))
    //     player->player_so = 1;
    // if (ft_strchr(str, 'W') && ft_strchr(str, 'E'))
    //     player->player_we = 1;
    // if (ft_strchr(str, 'E') && ft_strchr(str, 'A'))
    //     player->player_ea = 1;
    // result += player->player_ea + player->player_no + player->player_so + player->player_we;
    // if (result > 1) //test pour voir si plusieur player sur la carte
    //     return (-1);
    return (0);
}



// je pense check d'abord toutes les lignes 
// et ensuite toutes les colonnes
int isclosed(game_s *game, int x)
{
    size_t i;
    size_t y;
    int value_x;
    int value_y;

    i = 0;
    y = x;
    value_x = 1; //init a 1 pour eviter de return trop tot
    value_y = 1;
    while (game->map_data.map[y] && y < game->map_data.width)
    {
        i = 0;
        while(game->map_data.map[y][i] && game->map_data.map[y][i] == '\n')
            y++;
        printf("value de la premiere lign a check : %s\n", game->map_data.map[y]);
        while(game->map_data.map[y][i] && game->map_data.map[y][i] == ' ') //ici un check que le premier n'est pas un 0
            i++;
        if (check_last_value(game, y, i) == 0)
            return (0);
        while (game->map_data.map[y][i])
        {
            value_x = check_last_value(game, y, i);//ici un check que le dernier n'est pas un 0
            printf("value de la premiere lign a check : %c\n", game->map_data.map[y][i]);
            i++;  
        }
        printf("fin de ligne \n");
        if (value_x == 0)
            return (0);
        y++;
    }
    return (1);
}

int isclosed_column(game_s *game, int x)
{
    size_t i;
    size_t y;
    int value_x;
    int value_y;

    i = 0;
    y = x;
    value_x = 1; //init a 1 pour eviter de return trop tot
    value_y = 1;
    while (game->map_data.map[y][i])
    {
        y = x;
        while(game->map_data.map[y][i] && game->map_data.map[y][i] == '\n')
            y++;
        printf("value de la premiere lign a check : %s\n", game->map_data.map[y]);
        while(game->map_data.map[y][i] && game->map_data.map[y][i] == ' ')
            y++;
        if (game->map_data.map[y][i] && game->map_data.map[y][i] == '0') // ici check premier de la colonne
            return (0);
        while (game->map_data.map[y] && y < game->map_data.width)
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
    if (game->map_data.map[y][i] == '1')
        return (1);
    else if (game->map_data.map[y][i] == '0')
        return (0);
    else
        return (1);
}
