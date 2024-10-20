





#include "cub.h"

static int	alloc_tab(game_s *game, bool first_alloc)
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

/*
    . check if you got only one player in the map
    . check if all characteres in file are allowed
*/
static int	valid_file_content(char *buffer)
{
	static int	player;
	size_t		i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == 'N' || buffer[i] == 'S' || buffer[i] == 'E' || buffer[i] == 'W')
		{
			if (!player)
				player = 1;
			else
				return (ft_perror(E_MULTIPLAY));
		}
		if (is_valid_char(buffer[i]) == false)
			return (ft_perror(E_INVALID_CHAR));
		i++;
	}
    return (0);
}

static int	format_map(char **line)
{
	size_t	i;

	i = 0;
	while (line[0][i])
	{
		if (line[0][i] == '\n')
			line[0][i] = '\0';
		i++;
	}
	return (0);
}

static int	line_analysis(game_s *game, size_t *tab_size, char *buffer)
{
	static bool	flag;
	const bool	empty = is_empty_line(buffer);

	if (empty == true && game->map_data.map[0] != NULL && flag == 0)
        flag = 1;
	else if (empty == false && flag == 1)
		return (ft_perror(E_EMPTYLINE));
	if (empty == true)
        return (0);
    if (valid_file_content(buffer))
		return (1);
	game->map_data.map[*tab_size] = ft_strdup(buffer);
	if (!game->map_data.map[*tab_size])
		return (ft_perror("Crash malloc in line_analysis() in get_map()\n"));
	*tab_size += 1;
	return (format_map(&game->map_data.map[*tab_size - 1]));
}

int get_map(game_s *game, const int fd)
{
	char		*buffer;
	size_t		tab_size;

	if (alloc_tab(game, true))
		return (1);
	tab_size = 0;
	buffer = "buff";
	while (buffer != NULL)
	{
		if (tab_size == game->map_data.heigth)
			if (alloc_tab(game, false))
				return (free(buffer), 1);
		buffer = get_next_line(fd);
		if (!buffer)
			break ;
		if (line_analysis(game, &tab_size, buffer))
			return (free(buffer), 1);
		free(buffer);
	}
	if (tab_size == 0)
		return (ft_perror("Map is undefined\n"));
	else if (tab_size < 3)
		return (ft_perror("Invalid map description\n"));
	game->map_data.heigth = tab_size;
	return (0);
}
