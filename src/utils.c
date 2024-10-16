#include "cub.h"

char	**dup_map(game_s *game)
{
	size_t		y;
	char	**duplicate;

	y = 0;
	duplicate = (char **)malloc(sizeof(char *) * (game->map_data.width));
	while (y < game->map_data.width)
	{
		duplicate[y] = ft_strdup_get(game->map_data.map[y]);
		y++;
	}
	return (duplicate);
}
