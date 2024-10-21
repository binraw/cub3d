





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

int	check_lines(char **map, size_t heigth)
{
	size_t	x;
	size_t	y;

	y = 0;
	x = 0;
	while (map[y])
	{
		while(map[y][x] == ' ')
			x++;
		if (map[y][x] != '1')
		{
			printf("HERE y = %zu : x = %zu\n", y, x);
			return (1);
		}
		x = ft_strlen(map[y]) - 1;
		while (x != 0 && map[y][x] == ' ')
		{
			if (y > 0 && map[y - 1][x] == '0')
			{
				printf("HEERE\n");
				return (1);
			}
			if (y < heigth - 1 && map[y + 1][x] == '0')
			{
				printf("HEEERE\n");
				return (1);
			}
			x--;
		}
		if (map[y][x] == '0')
		{
			printf("HEEEERE\n");
			return (1);
		}
		x = 0;
		y++; 
	}
	return (0);
}

int	check_columns(char **map, size_t heigth, size_t width)
{
	size_t	x;
	size_t	y;

	y = 0;
	x = 0;
	while (y < heigth && map[y][x])
	{
		while (y < heigth && map[y][x] == ' ')
		{
			if (x != 0 && map[y][x - 1] == '0')
			{
				printf("HERE\n");
				return (1);
			}
			if (x < width && map[y][x + 1] == '0')
			{
				printf("HEERE\n");
				return (1);
			}
			y++;
		}
		if (map[y][x] != '1')
		{
			printf("HEEERE y = %zu : x == %zu\n", y, x);
			return (1);
		}
		y = heigth - 1;
		while (y != 0 && map[y][x] == ' ')
		{
			if (x > 0 && map[y][x - 1] == '0')
			{
				printf("HEEEERE\n");
				return (1);
			}
			if (x < width && map[y][x + 1] == '0')
			{
				printf("HEEEEERE\n");
				return (1);
			}
			y--;
		}
		y = 0;
		x++;
	}
}

int	check_map_validity(game_s *game)
{
	// char	**tmp;

	// game->plyr_data.pos_x = -1;
	// game->plyr_data.pos_y = -1;
	if (get_plyr_pos(game))
		return (1);
	// tmp = duplicate_map(game->map_data.map, game->map_data.heigth);
	// if (!tmp)
	// 	return (1);
	// flood_fill(game, tmp, (int) game->plyr_data.pos_x, \
	// 					(int) game->plyr_data.pos_y);
	
	
	if (check_lines(game->map_data.map, game->map_data.heigth))
		return (ft_perror("Map is not close in lines\n"));
	if (check_columns(game->map_data.map, game->map_data.heigth, game->map_data.width))
		return (ft_perror("Map is not close in columns\n"));
	
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
	close (fd);
	if (check_map_validity(game))
		return (free_map_data(game), 1);



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
