#include "../headers/cub.h"

char	**dup_map_pixel(game_s *game, int y)
{
	char	**duplicate;
	int i;


	i = 0;
	duplicate = (char **)malloc(sizeof(char *) * (game->num_line_map));
	while (y < game->num_line_map)
	{
		duplicate[i] = ft_strdup_get(game->file[y]);
		printf("valeur de la map : %s\n", duplicate[i]);
		i++;
		y++;
	}
	return (duplicate);
}
