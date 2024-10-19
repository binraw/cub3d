





#include "cub.h"

bool    is_valid_char(char c);

int process_create_map(game_s *game, char *file)
{
    // 1 -> recuperer orientation joueur et remplir la structure textures
    //  . return -1 error
    // int y;
    // printf("rentre dans le create map\n");
    // read_maap(file, game);
    // y = init_all_texture(game);
    // printf("valeur de y :%d\n", y);
    // if (y == -1) // gerer ici les free etc ..
    //     exit(1);
    // y++;
    // if (isclosed(game, y) == 0) // gerer ici les free etc ..
    //     exit(1);
    //  //if (isclosed_column(game, y) == 0) // reussir a faire fonctionner la fct qui permet de check
    //    // exit(1);
    // // en colonne si c'est bien 1 le dernier et pas un 0

    // if (init_pos_player(game, y) == -1) // gerer ici les free etc ..
    //     exit(1);
    // printf("Map valide bravo \n");
    return (0);
}

int	alloc_tab(game_s *game, bool first_alloc)
{
	char	**tmp;

	if (first_alloc == true)
	{
		game->map_data.map = ft_calloc(10, sizeof(char *));
		if (!game->map_data.map)
			return (ft_perror("Crash malloc in get_map()\n"));
		printf("in alloc : |%p|\n", game->map_data.map[0]);
		game->map_data.heigth = 10;
		return (0);
	}
	else
	{
		tmp = ft_realloc(game->map_data.map, (game->map_data.heigth + 10) * \
						sizeof(char*), game->map_data.heigth * sizeof(char*));
		if (!tmp)
			return (free_ptrtab(game->map_data.map), ft_perror("Crash realloc in get_map()\n"), 1);
		game->map_data.map = tmp;
		game->map_data.heigth += 10;
	}
	return (0);
}

bool    is_empty_line(char *buffer)
{
    size_t  i;

    i = 0;
    while (buffer[i])
    {
        if (buffer[i] != 9 && buffer[i] != 32 && buffer[i] != '\n')
            return (false);
        i++;
    }
    return (true);
}

/*
    . check if you got only one player in the map
    . check if all characteres in file are allowed
*/
int	valid_file_content(char *buffer)
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

/*
    . return 1 if detect the line as data of the texture
*/
int	skip_textures(char *buffer)
{
	if (buffer[1] == 'O' || buffer[1] == 'A' || buffer[1] == 'E' ||\
		buffer[0] == 'F' || buffer[0] == 'C')
		return (1);
	return (0);
}



static int	line_analysis(game_s *game, size_t *tab_size, char *buffer)
{
	static int	nb_textures;
    bool        empty;

    if (buffer[0] == '\n' && nb_textures < 6)
			return (0);
    if (skip_textures(buffer) == 1)
    {
        nb_textures += 1;
        return (0);
    }
    empty = is_empty_line(buffer);
    if (empty == false && nb_textures < 6)
        return (ft_perror(E_FILE_FORMAT));
	else if (empty == true && game->map_data.map[0] != NULL)
        return (ft_perror(E_EMPTYLINE));
    if (valid_file_content(buffer))
		return (1);
	printf("|%s|%p|", game->map_data.map[0], &game->map_data.map[0]);
	game->map_data.map[*tab_size] = ft_strdup(buffer);
	if (!game->map_data.map[*tab_size])
		return (ft_perror("Crash malloc in line_analysis() in get_map()\n"));
	*tab_size += 1;
	return (0);
}

int get_map(game_s *game, char *filepath)
{
	const int	fd = open(filepath, O_RDONLY);
	char		*buffer;
	size_t		tab_size;

	if (fd < 0)
		return (ft_perror("File cannot be opened in get_map()\n"));
	if (alloc_tab(game, true))
		return (close(fd), 1);
	tab_size = 0;
	buffer = "buff";
	while (buffer != NULL)
	{
		if (tab_size == game->map_data.heigth)
			if (alloc_tab(game, false))
				return (close(fd), free(buffer), 1);
		buffer = get_next_line(fd);
		if (!buffer)
			break ;
		if (line_analysis(game, &tab_size, buffer))
			return (close(fd), free(buffer), 1);
		free(buffer);
	}
	game->map_data.heigth = tab_size;
	return (close(fd));
}



int	parsing(game_s *game, char *filepath)
{
	ft_memset(game, 0, sizeof(game_s));
	ft_memset(game->texture.c_color, -1, 3 * sizeof(int));
	ft_memset(game->texture.f_color, -1, 3 * sizeof(int));
	// if (get_textures(game, filepath))
	// 	return (free_textures(game), 1);
    if (get_map(game, filepath))
        return (free_map_data(game), 1);

    // printf("%s\n", game->texture.text_no);
	// printf("%s\n", game->texture.text_so);
	// printf("%s\n", game->texture.text_ea);
	// printf("%s\n", game->texture.text_we);
	// printf("%d %d %d\n", game->texture.f_color[0], game->texture.f_color[1], game->texture.f_color[2]);
	// printf("%d %d %d\n\n\n", game->texture.c_color[0], game->texture.c_color[1], game->texture.c_color[2]);
	int i = 0;
	while(game->map_data.map[i])
		printf("%s", game->map_data.map[i++]);
	return (0);
}
