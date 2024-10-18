





#include "cub.h"


int process_create_map(game_s *game, char *file)
{
    // 1 -> recuperer orientation joueur et remplir la structure textures
    //  . return -1 error
    int y;
    printf("rentre dans le create map\n");
    read_maap(file, game);
    y = init_all_texture(game);
    printf("valeur de y :%d\n", y);
    if (y == -1) // gerer ici les free etc ..
        exit(1);
    y++;
    if (isclosed(game, y) == 0) // gerer ici les free etc ..
        exit(1);
     //if (isclosed_column(game, y) == 0) // reussir a faire fonctionner la fct qui permet de check
       // exit(1);
    // en colonne si c'est bien 1 le dernier et pas un 0

    if (init_pos_player(game, y) == -1) // gerer ici les free etc ..
        exit(1);
    printf("Map valide bravo \n");
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
		game->map_data.heigth = 10;
		return (0);
	}
	else
	{
		tmp = ft_realloc(game->map_data.map, (game->map_data.heigth + 10) * \
						sizeof(char*), game->map_data.heigth * sizeof(char*));
		if (!tmp)
			return (ft_perror("Crash realloc in get_map()\n"), 1);
		free(game->map_data.map);
		game->map_data.map = tmp;
		game->map_data.heigth += 10;
	}
	return (0);
}



int	valid_file_content(char *buffer)
{
	static int	player;
	bool		is_map;
	size_t		i;
	

	i = 0;
	is_map = false;
	player = 0;
	while (buffer[i] && is_map == false)
	{
		if (buffer[i] != '0' && buffer[i] != '1' && buffer[i] != 'N' && \
			buffer[i] != 'S' && buffer[i] != 'E' && buffer[i] != 'W' && \
			buffer[i] != '\n' && buffer[i] != ' ' && buffer[i] != 9)
			return (ft_perror("Invalid char in file\n"));
		if (buffer[i] == 'N' || buffer[i] == 'S' || buffer[i] == 'E' ||buffer[i] == 'W')
		{
			if (!player)
				player = 1;
			else
				return (ft_perror("Multiple player definition is forbidden\n"));
			is_map = true;
		}
		if (buffer[i] == '0' || buffer[i] == '1')
			is_map = true;
		i++;
	}

}



static int	line_analysis(game_s *game, size_t *tab_size, char *buffer)
{
	static int	nb_txt;

	if (buffer[1] == 'O' || buffer[1] == 'A' || buffer[1] == 'E' ||\
		buffer[0] == 'F' || buffer[0] == 'C' || buffer[0] == '\n')
	{
		nb_txt += 1;
		return (0);
	}
	if (valid_file_content(buffer))
		return (1);
	

	
	return (0);
}

int get_map(game_s *game, char *filepath)
{
	const int	fd = open(filepath, O_RDONLY);
	char		*buffer;
	size_t		tab_size;

	if (fd < 0)
		return (ft_perror("file can't be openin get_map()\n"));
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
	if (get_textures(game, filepath))
		return (free_textures(game), 1);
    if (get_map(game, filepath))
        return (free_map_data(game), 1);

    printf("%s\n", game->texture.text_no);
	printf("%s\n", game->texture.text_so);
	printf("%s\n", game->texture.text_ea);
	printf("%s\n", game->texture.text_we);
	printf("%d %d %d\n", game->texture.f_color[0], game->texture.f_color[1], game->texture.f_color[2]);
	printf("%d %d %d\n\n\n", game->texture.c_color[0], game->texture.c_color[1], game->texture.c_color[2]);
	int i = 0;
	while(game->map_data.map[i])
		printf("%s\n", game->map_data.map[i++]);
	return (0);
}
