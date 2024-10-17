#include "../headers/cub.h"

int	count_line_maap(char *file)
{
	int		count;
	int		fd;
	char	*lign;

	fd = open(file, O_RDONLY);
	count = -1;
	lign = "lign";
	while (lign != NULL)
	{
		lign = get_next_line(fd);
		free(lign);
		count++;
	}
	return (count);
}

void	alloc_lign(char *file, game_s *game)
{
	int		line_count;

	line_count = 0;
	game->numb_line = count_line_maap(file);
	game->file = malloc(sizeof(char *) * game->numb_line + 1);
	if (!game->file)
        return ; // rajouter des free 
}

void	read_file(char *file, game_s *game)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	game->map_data.width = 0;
	alloc_lign(file, game);
	if (!game->file)
		return ;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		return ;
	}
	game->map_data.heigth = count_line_maap(file);
	game->map_data.width = 0;
	while (i < game->map_data.heigth)
	{
		game->file[i] = get_next_line(fd);
		if (ft_strlen(game->file[i]) > game->map_data.width)
			game->map_data.width = ft_strlen(game->file[i]);
		i++;
	}
	close(fd);
}

int init_all_texture(game_s *game)
{
	size_t y;


	y = 0;
	game->texture.text_c = NULL;
	while (game->file[y] && !game->texture.text_c) // maniere de tout init pas top a changer
	{
		if (ft_strchr(game->file[y], 'N') && ft_strchr(game->file[y], 'O'))
			init_value_texture_no(game, y);
		if (ft_strchr(game->file[y], 'S') && ft_strchr(game->file[y], 'O'))
			init_value_texture_so(game, y);
		if (ft_strchr(game->file[y], 'W') && ft_strchr(game->file[y], 'E'))
			init_value_texture_we(game, y);
		if (ft_strchr(game->file[y], 'E') && ft_strchr(game->file[y], 'A'))
			init_value_texture_ea(game, y);
		if (ft_strchr(game->file[y], 'F'))
			init_value_texture_f(game, y);
		if (ft_strchr(game->file[y], 'C'))
			init_value_texture_c(game, y);
		y++;
	}
	if (control_texture_value(game) == 0)
			return (y);
	return (-1);
}

int control_texture_value(game_s *game)
{
	if (!game->texture.text_c || !game->texture.text_ea || !game->texture.text_f
	|| !game->texture.text_no || !game->texture.text_so || !game->texture.text_we)
		return (-1);
	else
		return (0);
}
