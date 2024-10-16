#include "../headers/cub.h"

char	**dup_map_pixel(game_s *game, int y)
{
	char	**duplicate;
	int i;

	i = 0;
	duplicate = (char **)malloc(sizeof(char *) * (game->numb_line_map));
	while (y < game->numb_line_map)
	{
		duplicate[i] = ft_strdup_get(game->map[y]);
		i++;
		y++;
	}
	return (duplicate);
}
