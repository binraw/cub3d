#include "cub.h"


int process_create_map(game_s *game, char *file)
{
    size_t y;


    read_maap(file, game);
    y = init_all_texture(game);
    if (y == -1) // gerer ici les free etc ..
        exit(1);
    if (isclosed(game, y) == 0) // gerer ici les free etc ..
        exit(1);
    
    return (0);
}


int control_valide_map(game_s *game, size_t y)
{

}



int check_map_close(game_s *game, size_t y)
{
    size_t i;

    i = 0;
    while(game->map[y][i] == '\n')
        y++;
    
}
// je pense check d'abord toutes les lignes 
// et ensuite toutes les colonnes
int isclosed(game_s *game, size_t x)
{
    size_t i;
    size_t y;
    int value_x;
    int value_y;

    i = 0;
    y = x;
    value_x = 0;
    value_y = 0;
    while (game->map[y])
    {
        i = 0;
        while (game->map[y][i])
        {
            value_x = check_last_value(game, y, i);
            i++;

        }
        if (value_x == 0)
            return (0);
        y++;
    }
    y = x;
    i = 0;
    while (game->map[y][i])
    {
        y = x;
        while(game->map[y][i] == ' ')
            y++;
        if (game->map[y][i] == '0')
            return (0);
        while (game->map[y][i])
        {
            value_y = check_last_value(game, y, i);
            y++;
        }
        if (value_y == 0)
            return (0);
        i++;
    }
    return (1);
}

int check_last_value(game_s *game, size_t y, size_t i)
{
    if (game->map[y][i] == ' 1')
        return (1);
    else if (game->map[y][i] == '0')
        return (0);
    else
        return (1);
}
