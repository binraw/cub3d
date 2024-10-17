





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

int	fill_textures(char *buff_f, void **buff_t, bool is_dir)
{
	size_t	i;

	i = 2;
	if (is_dir)
	{
		while (buff_f[i] && buff_f[i] != ' ')
			i++;
		*buff_t = ft_substr(buff_f, i, ft_strlen(buff_f) - i);
		if (!*buff_t)
			return (ft_perror("crash malloc in fill_textures\n"), -1);
	}
	else
	{
		;
	}
	return (0);
}

int	line_analysis(game_s *game, char *buffer)
{
	int	ret_value;

	// no empty line in this function !!!
	if (buffer[0] != '\0' && buffer[0] == 'N' && buffer[1] == 'O')
		ret_value = fill_textures(buffer, (void **) &game->texture.text_no, 1);
	else if (buffer[0] != '\0' && buffer[0] == 'S' && buffer[1] == 'O')
		ret_value = fill_textures(buffer, (void **) &game->texture.text_so, 1);
	else if (buffer[0] != '\0' && buffer[0] == 'E' && buffer[1] == 'A')
		ret_value = fill_textures(buffer, (void **) &game->texture.text_ea, 1);
	else if (buffer[0] != '\0' && buffer[0] == 'W' && buffer[1] == 'E')
		ret_value = fill_textures(buffer, (void **) &game->texture.text_we, 1);
	else if (buffer[0] == 'F')
		ret_value = fill_textures(buffer, (void **) &game->texture.f_color, 0);
	else if (buffer[0] == 'C')
		ret_value = fill_textures(buffer, (void **) &game->texture.c_color, 0);
	else
		; // return error
	// check if all textures are fill -> texture.all_text = 1
	return (0);
}

int	get_text_path(game_s *game, char *filepath, int fd)
{
	char		*buffer;

	buffer = "buf";
	while (buffer != NULL && game->texture.all_text != 0)
	{
		buffer = get_next_line(fd);
		if (!buffer)
			break ;
		if (buffer[0] == '\n' || buffer[0] == '\0')
			continue ;
		else if (line_analysis(game, buffer))
			return (free(buffer), free_textures(game), 1);
		free(buffer);
	}
	printf("%s\n", game->texture.text_no);
	printf("%s\n", game->texture.text_so);
	printf("%s\n", game->texture.text_ea);
	printf("%s\n", game->texture.text_we);
	if (game->texture.all_text != 1)
	{
		free_textures(game);
		return (ft_perror("Texture data are invalid\n")); // free_memory
	}
	return (0);
}

int	parsing(game_s *game, char *filepath)
{
	const int	fd = open(filepath, O_RDONLY);

	if (fd < 0)
		return (ft_perror("file can't be open\n"));
	ft_memset(game, 0, sizeof(game_s));
	if(get_text_path(game, filepath, fd))
		return (1);

	return (0);
}
