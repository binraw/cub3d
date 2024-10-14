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
	int	i;
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
		error_game(game);
		return ;
	}
	game->numb_line = count_line_maap(file);
	while (i < game->numb_line)
	{
		game->map[i] = get_next_line(fd);
		i++;
	}
	close(fd);
}

int init_all_texture(game_s *game)
{
	size_t i;
	size_t y;

	i = 0;
	y = 0;
	while (game->map[y])
	{
		while (game->map[y][i] != '\n')
		{
			if (init_value_texture_no(game, y) != -1 || init_value_texture_so(game, y) != -1
			|| init_value_texture_we(game, y) != -1 || init_value_texture_ea(game, y) != -1
			|| init_value_texture_f(game, y) != -1 || init_value_texture_c(game, y) != -1)
				break ;
			i++;
		}
		if (control_texture_value(game) == 0)
			return (y);
		y++;
	}
	return (-1);
}

int control_texture_value(game_s *game)
{
	if (!game->text_c || !game->text_ea || !game->text_f
	|| !game->text_no || !game->text_so || !game->text_we)
		return (-1);
	else
		return (0);
}