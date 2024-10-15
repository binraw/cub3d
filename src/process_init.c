#include "cub.h"


int process_create_map(game_s *game, char *file)
{
    int y;

    ft_bzero(game, sizeof(game_s));
    read_maap(file, game);
    y = init_all_texture(game);
    if (y == -1) // gerer ici les free etc ..
        exit(1);
    if (isclosed(game, y) == 0) // gerer ici les free etc ..
        exit(1);
    if (init_pos_player(game, y) == -1) // gerer ici les free etc ..
        exit(1);
    printf("Map valide bravo \n");
    return (0);
}


int init_pos_player(game_s *game, int y)
{
    player_s player;
    size_t i;

    i = 0;
    // ft_bzero((void*)player, sizeof(player_s));
    while(game->map[y])
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
    while (game->map[y])
    {
        i = 0;
        while(game->map[y][i] && game->map[y][i] == ' ') //ici un check que le premier n'est pas un 0
            i++;
        if (check_last_value(game, y, i) == 0)
            return (0);
        while (game->map[y][i])
        {
            value_x = check_last_value(game, y, i);//ici un check que le dernier n'est pas un 0
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
        if (game->map[y][i] == '0') // ici check premier de la colonne
            return (0);
        while (game->map[y][i])
        {
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
