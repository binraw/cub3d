/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:02:42 by fberthou          #+#    #+#             */
/*   Updated: 2024/10/24 21:15:03 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	game->plyr_data.pos_x = -1;
	game->plyr_data.pos_y = -1;
	return (0);
}

static void	fill_player_data(game_s *game, char orientation)
{
	if (orientation == 'N')
	{
		game->plyr_data.angle = ANGLE_N;
		game->plyr_data.dir_x = 0;
		game->plyr_data.dir_y = -1;
	}
	else if (orientation == 'S')
	{
		game->plyr_data.angle = ANGLE_S;
		game->plyr_data.dir_x = 0;
		game->plyr_data.dir_y = 1;
	}
	else if (orientation == 'E')
	{
		game->plyr_data.angle = ANGLE_E;
		game->plyr_data.dir_x = 1;
		game->plyr_data.dir_y = 0;
	}
	else
	{
		game->plyr_data.angle = ANGLE_W;
		game->plyr_data.dir_x = -1;
		game->plyr_data.dir_y = 0;
	}
}

static int	get_plyr_pos(game_s *game)
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
				fill_player_data(game, game->map_data.map[y][x]);
				game->plyr_data.initial_angle = game->plyr_data.angle;
				return (0);
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

int	parsing(game_s *game, char *filepath)
{
	const int	fd = open(filepath, O_RDONLY);

	if (init_parsing(filepath, game, fd))
		return (1);
	if (get_textures(game, fd))
		return (free_textures(game), close(fd), 1);
	if (get_map(game, fd))
		return (free_map_data(game), close(fd), 1);
	close(fd);
	if (check_map_validity(game))
		return (free_map_data(game), 1);
	return (get_plyr_pos(game));
}
