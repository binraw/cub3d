/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:02:42 by fberthou          #+#    #+#             */
/*   Updated: 2024/11/26 20:39:29 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	init_data_angle(t_game *game, float angle, int x, int y)
{
	game->plyr_data.angle = angle;
	game->plyr_data.dir_x = x;
	game->plyr_data.dir_y = y;
}

static int	init_parsing(char *filepath, t_game *game, const int fd)
{
	int	i;

	i = 0;
	if (fd < 3)
		return (perror("Cannot open file\n"), -1);
	i = ft_strlen(filepath);
	if (i-- < 5)
		return (close(fd), ft_perror("Invalid filename\n"));
	if (filepath[i] != 'b' || filepath[i - 1] != 'u' || \
		filepath[i - 2] != 'c' || filepath[i - 3] != '.')
		return (close(fd), ft_perror("Bad file extension\n"));
	ft_memset(game, 0, sizeof(t_game));
	ft_memset(game->texture.c_color, -1, 3 * sizeof(int));
	ft_memset(game->texture.f_color, -1, 3 * sizeof(int));
	game->plyr_data.pos_x = -1;
	game->plyr_data.pos_y = -1;
	return (0);
}

static void	fill_player_data(t_game *game, char orientation)
{
	if (orientation == 'N')
		init_data_angle(game, ANGLE_N, 0, -1);
	else if (orientation == 'S')
		init_data_angle(game, ANGLE_S, 0, 1);
	else if (orientation == 'E')
		init_data_angle(game, ANGLE_E, 1, 0);
	else
		init_data_angle(game, ANGLE_W, -1, 0);
	game->plyr_data.plane_x = -game->plyr_data.dir_y * tan(FOV_2);
	game->plyr_data.plane_y = game->plyr_data.dir_x * tan(FOV_2);
}

static int	get_plyr_pos(t_game *game)
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
				fill_player_data(game, game->map_data.map[y][x]);
				game->plyr_data.pos_x = (double)(x * TILE_S + (TILE_S >> 1));
				game->plyr_data.pos_y = (double)(y * TILE_S + (TILE_S >> 1));
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

int	parsing(t_game *game, char *filepath)
{
	const int	fd = open(filepath, O_RDONLY);

	if (init_parsing(filepath, game, fd))
		return (1);
	if (get_textures(game, fd))
		return (free_textures(game), close(fd), 1);
	if (get_map(game, fd))
		return (close(fd), free_textures(game), 1);
	if (close(fd) == -1)
	{
		free_map(game->map_data.map, game->map_data.heigth);
		free_textures(game);
		perror("Function close crash in parsing ");
		return (-1);
	}
	if (check_map_validity(game))
		return (free_map_data(game), 1);
	if (get_plyr_pos(game))
		return (free_map_data(game), 1);
	return (0);
}
