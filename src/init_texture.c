#include "cub.h"

int init_value_texture_no(game_s *game, size_t y)
{

    size_t i;

    printf("rentre dans init texture no \n");
    i = 0;
    if (game->map[y][i] == 'N')
        if (game->map[y][i + 1] == 'O')
        {
            i = 2;
            while (game->map[y][i] != '\n')
                i++;
            i -= 2;
            game->text_no = malloc(i * sizeof(char));
            if (!game->text_no)
                return (-1);
        }
    i += 2;
    
    game->text_no = ft_strjoin(NULL, game->map[y]);
    printf("valeur de text_no : %s\n", game->text_no);
    printf("sors d'init texture no \n\n");
    if (!game->text_no)
        return (-1);
    return (0);
}


int init_value_texture_so(game_s *game, size_t y)
{

    size_t i;

    i = 0;
    if (game->map[y][i] == 'S')
        if (game->map[y][i + 1] == 'O')
        {
            i = 2;
            while (game->map[y][i] != '\n')
                i++;
            i -= 2;
            game->text_so = malloc(i * sizeof(char));
            if (!game->text_so)
                return (-1);
        }
    i += 2;
    game->text_so = ft_strjoin(NULL, game->map[y]);
    printf("valeur de text_so : %s\n", game->text_so);
    printf("sors d'init texture so \n\n");
    if (!game->text_so)
        return (-1);
    return (0);
}

int init_value_texture_we(game_s *game, size_t y)
{

    size_t i;

    i = 0;
    if (game->map[y][i] == 'W')
        if (game->map[y][i + 1] == 'E')
        {
            i = 2;
            while (game->map[y][i] != '\n')
                i++;
            i -= 2;
            game->text_we = malloc(i * sizeof(char));
            if (!game->text_we)
                return (-1);
        }
    i += 2;
    game->text_we = ft_strjoin(NULL, game->map[y]);
    printf("valeur de text_we : %s\n", game->text_we);
    printf("sors d'init texture we \n\n");
    if (!game->text_we)
        return (-1);
    return (0);
}

int init_value_texture_ea(game_s *game, size_t y)
{

    size_t i;

    i = 0;
    if (game->map[y][i] == 'E')
        if (game->map[y][i + 1] == 'A')
        {
            i = 2;
            while (game->map[y][i] != '\n')
                i++;
            i -= 2;
            game->text_ea = malloc(i * sizeof(char));
            if (!game->text_ea)
                return (-1);
        }
    i += 2;
    game->text_ea = ft_strjoin(NULL, game->map[y]);
    printf("valeur de text_ea : %s\n", game->text_ea);
    printf("sors d'init texture ea \n\n");
    if (!game->text_ea)
        return (-1);
    return (0);
}

int init_value_texture_f(game_s *game, size_t y)
{

    size_t i;

    i = 0;
    if (game->map[y][i] == 'F')
	{
		i = 1;
		while (game->map[y][i] != '\n')
			i++;
		i -= 1;
		game->text_f = malloc(i * sizeof(char));
		if (!game->text_no)
			return (-1);
	}
    i += 1;
    game->text_f = ft_strjoin(NULL, game->map[y]);
    printf("valeur de text_f : %s\n", game->text_f);
    printf("sors d'init texture f \n\n");
    if (!game->text_f)
        return (-1);
    return (0);
}


int init_value_texture_c(game_s *game, size_t y)
{

    size_t i;

    i = 0;
    if (game->map[y][i] == 'C')
	{
		i = 1;
		while (game->map[y][i] != '\n')
			i++;
		i -= 1;
		game->text_c = malloc(i * sizeof(char));
		if (!game->text_no)
			return (-1);
	}
    i += 1;
    game->text_c = ft_strjoin(NULL, game->map[y]);
    printf("valeur de text_c : %s\n", game->text_c);
    printf("sors d'init texture c \n\n");
    if (!game->text_c)
        return (-1);
    return (0);
}