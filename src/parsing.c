





#include "cub.h"

static int	init_parsing(char *filepath, game_s *game, const int fd)
{
	int	i;

	i = 0;
	if (fd < 3)
		return (ft_perror("Cannot open file, check the path and the name\n"));
	while (filepath[i])
        i++;
    if (i-- < 5)
        return (close(fd), ft_perror("Invalid filename\n"));
	if (filepath[i] != 'b' || filepath[i - 1] != 'u' || \
		filepath[i - 2] != 'c' || filepath[i - 3] != '.')
		return (close(fd), ft_perror("Bad file extension\n"));
	ft_memset(game, 0, sizeof(game_s));
	ft_memset(game->texture.c_color, -1, 3 * sizeof(int));
	ft_memset(game->texture.f_color, -1, 3 * sizeof(int));
	return (0);
}


int	fill_player_data(game_s *game, char orientation, size_t x, size_t y)
{
	if (orientation == 'N')
	{
		game->plyr_data.angle = ANGLE_N;
		game->plyr_data.dir_x = 0;
		game->plyr_data.dir_y = -1;
	}
	else if (orientation == 'S')
	{
		game->plyr_data.dir_x = 0;
		game->plyr_data.dir_y = 1;
		game->plyr_data.angle = ANGLE_S;
	}
	else if (orientation == 'E')
	{
		game->plyr_data.dir_x = 1;
		game->plyr_data.dir_y = 0;
		game->plyr_data.angle = ANGLE_E;
	}
	else
	{
		game->plyr_data.dir_x = -1;
		game->plyr_data.dir_y = 0;
		game->plyr_data.angle = ANGLE_W;
	}
	return (0);
}

int	get_plyr_pos(game_s *game)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (game->map_data.map[y])
	{
		while (game->map_data.map[y][x])
		{
			if (is_player(game->map_data.map[y][x]))
			{
				game->plyr_data.pos_x = (float) x;
				game->plyr_data.pos_y = (float) y;
				return (fill_player_data(game, game->map_data.map[y][x], x, y));
			}
			x++;
		}
		x = 0;
		y++;
	}
	if (game->plyr_data.pos_x == -1)
		return (ft_perror("No player position\n"));
	return (0);
}

void	flood_fill(game_s *game, char **map, size_t x, size_t y)
{
	if (y < game->map_data.heigth)
	{
		game->map_data.tmp = ft_strlen(map[y]);
		if (game->map_data.tmp > game->map_data.width)
			game->map_data.width = game->map_data.tmp;
	}
	else
		return ;
	if (x >= game->map_data.tmp)
		return ;
	if (map[y][x] == 'v' || map[y][x] == ' ' || map[y][x] == '\t')
		return ;
	else if ((y == 0 || x == 0 || x + 1 == ft_strlen(map[y]) && \
			map[y][x] == '1'))
		return ;
	else if (map[y][x] == '1')
		map[y][x] = '1';
	else
		map[y][x] = 'v';
	// if (y < game->map_data.heigth)
	flood_fill(game, map, x, (y + 1));
	// if (y)
	flood_fill(game, map, x, (y - 1));
	// if (map[y] && map[y][x])
	flood_fill(game, map, (x + 1), y);
	// if (x != 0)
	flood_fill(game, map, (x - 1), y);
}

int	check_first_last_line(char **tmp, size_t x, size_t y)
{
	while (tmp[0][x])
	{
		if (tmp[0][x] == 'v' || tmp[0][x] == '0')
				return (ft_perror("Map is not closed\n"));
		x++;
	}
	while (tmp[y])
		y++;
	y--;
	x = 0;
	while (tmp[y][x])
	{
		if (tmp[y][x] == 'v' || tmp[y][x] == '0')
				return (ft_perror("Map is not closed\n"));
		x++;
	}
	return (0);
}

bool	map_is_close(char **tmp, game_s *game)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	if (check_first_last_line(tmp, x, y))
		return (false);

	return (true);
}

int	check_map_validity(game_s *game)
{
	char	**tmp;

	game->plyr_data.pos_x = -1;
	game->plyr_data.pos_y = -1;
	if (get_plyr_pos(game))
		return (1);
	tmp = duplicate_map(game->map_data.map, game->map_data.heigth);
	if (!tmp)
		return (1);
	flood_fill(game, tmp, (size_t) game->plyr_data.pos_x, \
						(size_t) game->plyr_data.pos_y);
	// if (map_is_close(tmp, game) == false)
	// 	return (free_ptrtab(tmp), 1);
	for (int i = 0; i < game->map_data.heigth; i++){
		printf("%s\n", tmp[i]);
	}
	free_ptrtab(tmp);
	return (0);
}


int	parsing(game_s *game, char *filepath)
{
	const int	fd = open(filepath, O_RDONLY);

	if (init_parsing(filepath, game, fd))
		return (1);
	if (get_textures(game, fd))
		return (free_textures(game), close(fd), 1);
    if (get_map(game, fd))
        return (free_map_data(game), close(fd), 1);
	if (check_map_validity(game))
		return (free_map_data(game), close(fd), 1);


    printf("%s\n", game->texture.text_no);
	printf("%s\n", game->texture.text_so);
	printf("%s\n", game->texture.text_ea);
	printf("%s\n", game->texture.text_we);
	printf("%d %d %d\n", game->texture.f_color[0], game->texture.f_color[1], game->texture.f_color[2]);
	printf("%d %d %d\n\n\n", game->texture.c_color[0], game->texture.c_color[1], game->texture.c_color[2]);
	int i = 0;
	// while(game->map_data.map[i])
	// 	printf("%s\n", game->map_data.map[i++]);
	printf("map size == %zu\n", game->map_data.heigth);
	printf("player pos : x == %f : y == %f\n", game->plyr_data.pos_x, game->plyr_data.pos_y);
	return (close(fd), 0);
}
