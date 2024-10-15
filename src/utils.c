#include "cub.h"

char	**dup_map(game_s *game)
{
	int		y;
	char	**duplicate;

	y = 0;
	duplicate = (char **)malloc(sizeof(char *) * (game->numb_line));
	while (y < game->numb_line)
	{
		duplicate[y] = ft_strdup_get(game->map[y]);
		y++;
	}
	return (duplicate);
}
