#include "cub.h"

bool	is_player(char c)
{
	return (c == 'N' || c == 'S' || \
			c == 'E' || c == 'W');
}

bool    is_valid_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || \
			c == 'S' || c == 'E' || c == 'W' || \
			c == '\n' || c == ' ');
}

bool	is_empty_line(char *buffer)
{
    size_t  i;

    i = 0;
    if (buffer[1] == 'O' || buffer[1] == 'A' || buffer[1] == 'E' || \
        buffer[0] == 'F' || buffer[0] == 'C')
        return (true);
    while (buffer[i])
    {
    if (buffer[i] != 9 && buffer[i] != 32 && buffer[i] != '\n')
            return (false);
        i++;
    }
    return (true);
}

char	**duplicate_map(char **src, size_t nb_ptr)
{
	char	**tmp;
	size_t	i;

	tmp = ft_calloc(nb_ptr + 1, sizeof(char *));
	if (!tmp)
		return (ft_perror("Crash malloc tmp in duplicate_map()\n"), NULL);
	i = 0;
	while (i < nb_ptr)
	{
		tmp[i] = ft_strdup(src[i]);
		if (tmp[i] == NULL)
			return (free_ptrtab(tmp), \
					ft_perror("Crash malloc strdup in duplicate_map()\n"), NULL);
		i++;
	}
	return (tmp);
}

int	alloc_tab(game_s *game, bool first_alloc)
{
	char	**tmp;

	if (first_alloc == true)
	{
		game->map_data.map = ft_calloc(10, sizeof(char *));
		if (!game->map_data.map)
			return (ft_perror("Crash malloc in get_map()\n"));
		game->map_data.heigth = 10;
		return (0);
	}
	else
	{
		tmp = ft_realloc(game->map_data.map, (game->map_data.heigth + 10) * \
						sizeof(char*), game->map_data.heigth * sizeof(char*));
		if (!tmp)
			return (free_ptrtab(game->map_data.map), \
					ft_perror("Crash realloc in get_map()\n"), 1);
		game->map_data.map = tmp;
		game->map_data.heigth += 10;
	}
	return (0);
}
