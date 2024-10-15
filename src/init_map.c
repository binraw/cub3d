#include "cub.h"

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
	line_count = count_line_maap(file);
	game->map = malloc(sizeof(char *) * line_count + 1);
	if (!game->map)
        return ; // rajouter des free 
}

void	read_maap(char *file, game_s *game)
{
	size_t	i;
	int	fd;

	i = 0;
	fd = 0;
	game->numb_line = 0;
	alloc_lign(file, game);
	if (!game->map)
		return ;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		
		return ;
	}
	game->numb_line = count_line_maap(file);
	while (i < game->numb_line)
	{
		game->map[i] = get_next_line(fd);
		i++;
	}
	printf(" valeur de la premiere ligne du fichier : \n %s\n", game->map[0]);
	printf("fini de lire le fichier\n");
	close(fd);
}

int init_all_texture(game_s *game)
{
	size_t i;
	size_t y;

	i = 0;
	y = 0;
	game->text_c = NULL;
	while (game->map[y] && !game->text_c) // maniere de tout init pas top a changer
	{
		if (ft_strchr(game->map[y], 'N') && ft_strchr(game->map[y], 'O'))
			init_value_texture_no(game, y);
		if (ft_strchr(game->map[y], 'S') && ft_strchr(game->map[y], 'O'))
			init_value_texture_so(game, y);
		if (ft_strchr(game->map[y], 'W') && ft_strchr(game->map[y], 'E'))
			init_value_texture_we(game, y);
		if (ft_strchr(game->map[y], 'E') && ft_strchr(game->map[y], 'A'))
			init_value_texture_ea(game, y);
		if (ft_strchr(game->map[y], 'F'))
			init_value_texture_f(game, y);
		if (ft_strchr(game->map[y], 'C'))
			init_value_texture_c(game, y);
		y++;
	}
	if (control_texture_value(game) == 0)
			return (y);
	return (-1);
}

int control_texture_value(game_s *game)
{
	// printf("les differentes values : %s\n %s\n %s\n %s\n %s\n %s\n", game->text_c, game->text_ea, game->text_f, game->text_no, game->text_so, game->text_we);
	if (!game->text_c || !game->text_ea || !game->text_f
	|| !game->text_no || !game->text_so || !game->text_we)
		return (-1);
	else
		return (0);
}