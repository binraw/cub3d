#include "../headers/cub.h"


// int process_create_map(game_s *game, char *file)
// {
//     // recuperer les textures dans le fichier
//     // recuperer map
//         // -> VERIFIER CARACTERE AUTORISEES 0 1 n s e w
//     int y;
//     printf("rentre dans le create map\n");
//     read_file(file, game);
//     y = init_all_texture(game);

//     printf("valeur de y :%d\n", y);
//     if (y == -1) // gerer ici les free etc ..
//         exit(1);
//     y++;
//     init_pixel_map(game, y);
//     init_value_player(game);
//     if (isclosed(game) != 0) // gerer ici les free etc ..
//         exit(1);
    
//     printf("Map valide bravo \n");
//     return (0);
// }

// int init_pixel_map(game_s *game, int y)
// {
//     game->num_line_map = 0;
//     printf("%d\n", game->numb_line);
//     game->num_line_map = game->numb_line - y;
//     printf("%d\n", game->num_line_map);
//     game->map = dup_map_pixel(game, y);
// 	if (!game->map)
//         return (-1);
//     return (0);
// }

// int init_value_player(game_s *game)
// {
//     printf("rentre bien dans init player\n");
//     size_t y;
//     size_t i;

//     y = 0;
//     i = 0;
    
//     while(game->map[y])
//     {
//         while(game->map[y][i])
//         {
//             if (value_player(game, game->map[y][i]) == -1)
//                 return (-1); // en cas ou de 2 players
//             i++;
//         }
//         y++;
//     }
//     return (0);
// }

int value_player(game_s *game, char c)
{
    if (c == 'N')
    {
        if (!game->plyr_data.value_player)
            game->plyr_data.value_player = 'N';
        else
            return (-1);
    }
    else if (c == 'S')
    {
        if (!game->plyr_data.value_player)
            game->plyr_data.value_player = 'S';
        else
            return (-1);
    }
    else if (c == 'W')
    {
        if (!game->plyr_data.value_player)
            game->plyr_data.value_player = 'W';
        else
            return (-1);
    }
    else if (c == 'E')
    {
        if (!game->plyr_data.value_player)
           game->plyr_data.value_player = 'E';
        else
            return (-1);
    }
    else
        return (0);
    return (0);
}


// int init_pos_player(game_s *game, int x)
// {
//     player_s player;
//     int y;

//     y = x;
//     while(game->map[y] && y < game->numb_line)
//     {
//         if (control_value_player(&player, game->map_data.map[y]) == -1)
//             return (-1);
//         y++;
//     }
//     return (0);
// }

// int    control_value_player(player_s *player, char *str)
// {
//     (void) player;
//     (void) str;
//     // int result;

//     // result = 0;
//     // if (ft_strchr(str, 'N') && ft_strchr(str, 'O'))
//     //     player->player_no = 1;
//     // if (ft_strchr(str, 'S') && ft_strchr(str, 'O'))
//     //     player->player_so = 1;
//     // if (ft_strchr(str, 'W') && ft_strchr(str, 'E'))
//     //     player->player_we = 1;
//     // if (ft_strchr(str, 'E') && ft_strchr(str, 'A'))
//     //     player->player_ea = 1;
//     // result += player->player_ea + player->player_no + player->player_so + player->player_we;
//     // if (result > 1) //test pour voir si plusieur player sur la carte
//     //     return (-1);
//     return (0);
// }




// int isclosed(game_s *game)
// {
//     int i;
//     int y;
//     int result;

//     printf("rentre bien dans le controle\n");
//     i = 1;
//     y = 1;
//     result = 0;
//     while(game->map[y + 1])
//     {
//         i = 1;
//         while(game->map[y][i] != '\n' && game->map[y][i + 1])
//         {
//             if (game->map[y][i] == '0')
//             {
//                 result += check_last_value(game, y, i + 1);
//                 result += check_last_value(game, y, i - 1);
//                 result += check_last_value(game, y + 1, i);
//                 result += check_last_value(game, y - 1, i);
//                 if (result > 0)
//                 {
//                     printf("sors en mode erreur\n");
//                     return (-1);
//                 }
//             }
//             i++;
//         }
//     y++;
//     }
//     printf("sors bien\n");
//     return (0);
// }

// int no_player_in_wall(game_s *game)
// {
//     int i;
//     int y;
//     int result;

//     i = 1;
//     y = 1;
//     result = 0;
//     while(game->map[y + 1])
//     {
//         i = 1;
//         while(game->map[y][i] != '\n' && game->map[y][i + 1])
//         {
//             if (game->map[y][i] == game->plyr_data.value_player)  // mettre valeur du personnage
//             {
//                 result += check_last_value(game, y, i + 1);
//                 result += check_last_value(game, y, i - 1);
//                 result += check_last_value(game, y + 1, i);
//                 result += check_last_value(game, y - 1, i);
//                 if (result > 0)
//                     return (-1);
//             }
//             i++;
//         }
//     y++;
//     }
//     return (0);
// }


// int check_last_value(game_s *game, int y, int i)
// {
//     // if (game->map[y][i] == '0' || game->map[y][i] == '1')
//     //     return (0);
//     // else if (game->map[y][i] == 'N' || game->map[y][i] == 'S'
//     //     || game->map[y][i] == 'W' || game->map[y][i] == 'E')
//     //     return (0);
//     if (game->map[y][i] == ' ')
//         return (1);
//     return (0);
// }
