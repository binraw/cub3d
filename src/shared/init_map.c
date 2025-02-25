/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:08:50 by fberthou          #+#    #+#             */
/*   Updated: 2024/11/27 20:14:40 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "get_next_line.h"

static int	valid_file_content(char *buffer)
{
	static int	player;
	size_t		i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == 'N' || buffer[i] == 'S' || \
			buffer[i] == 'E' || buffer[i] == 'W')
		{
			if (!player)
				player = 1;
			else
				return (ft_perror(E_MULTIPLAY));
		}
		if (is_valid_char(buffer[i]) == false)
			return (ft_perror(E_INVALID_CHAR));
		i++;
	}
	return (0);
}

int	format_line(char **line, size_t *length)
{
	int	i;

	i = 0;
	while (line[0] && line[0][i])
	{
		if (line[0][i] == '\n')
			line[0][i] = '\0';
		i++;
	}
	i -= 1;
	if (length != NULL && i > (int)*length)
		*length = (size_t)i;
	return (0);
}

static int	format_map(t_game *game)
{
	char	*tmp;
	char	*temp;
	size_t	len;
	size_t	y;

	y = 0;
	while (y < game->map_data.heigth)
	{
		len = ft_strlen(game->map_data.map[y]);
		if (len < game->map_data.width)
		{
			tmp = ft_calloc(game->map_data.width - len + 1, sizeof(char));
			if (!tmp)
				return (ft_perror("Crash malloc in format_map()\n"));
			ft_memset(tmp, ' ', game->map_data.width - len);
			temp = ft_strjoin(game->map_data.map[y], tmp);
			free(tmp);
			if (!temp)
				return (ft_perror("Crash ft_strjoin()\n"));
			free(game->map_data.map[y]);
			game->map_data.map[y] = temp;
		}
		y++;
	}
	return (0);
}

static int	line_analysis(t_game *game, size_t *tab_size, char *buffer)
{
	static bool	flag;
	const bool	empty = is_empty_line(buffer);

	if (empty == true && game->map_data.map[0] != NULL && flag == 0)
		flag = 1;
	else if (empty == false && flag == 1)
		return (ft_perror(E_EMPTYLINE));
	if (empty == true)
		return (0);
	if (valid_file_content(buffer))
		return (1);
	game->map_data.map[*tab_size] = ft_strdup(buffer);
	if (!game->map_data.map[*tab_size])
		return (ft_perror("Crash malloc in line_analysis() in get_map()\n"));
	format_line(&game->map_data.map[*tab_size], &game->map_data.width);
	*tab_size += 1;
	return (0);
}

int	get_map(t_game *game, const int fd)
{
	char		*buffer;
	size_t		tab_size;

	if (alloc_tab(game, true))
		return (1);
	tab_size = 0;
	buffer = "buff";
	while (buffer != NULL)
	{
		if (tab_size == game->map_data.heigth)
			if (alloc_tab(game, false))
				return (free_map(game->map_data.map, tab_size), 1);
		buffer = get_next_line(fd);
		if (!buffer)
			break ;
		if (line_analysis(game, &tab_size, buffer))
			return (destroy_bad_line(game, buffer), 1);
		free(buffer);
	}
	if (tab_size == 0)
		return (free_map(game->map_data.map, tab_size), ft_perror(E_EMPTY));
	if (tab_size < 3)
		return (free_map(game->map_data.map, tab_size), ft_perror(E_MAP_DESC));
	game->map_data.heigth = tab_size;
	return (format_map(game));
}
