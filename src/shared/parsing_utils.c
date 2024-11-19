/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:02:35 by fberthou          #+#    #+#             */
/*   Updated: 2024/11/19 09:45:17 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	is_player(char c)
{
	return (c == 'N' || c == 'S' || \
			c == 'E' || c == 'W');
}

bool	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || \
			c == 'S' || c == 'E' || c == 'W' || \
			c == '\n' || c == ' ' || c == '\t');
}

bool	is_empty_line(char *buffer)
{
	size_t	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] != '\t' && buffer[i] != ' ' && buffer[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

char	**duplicate_map(char **src, size_t nb_ptr)
{
	char	**tmp;
	size_t	i;

	tmp = ft_calloc(nb_ptr + 1, sizeof(char *));
	if (!tmp)
		return (ft_perror("Crash malloc tmp in duplicate_map()\n"), NULL);
	i = 0;
	while (i < nb_ptr)
	{
		tmp[i] = ft_strdup(src[i]);
		if (tmp[i] == NULL)
			return (free_map(tmp, i), \
					ft_perror("Crash strdup in duplicate_map()\n"), NULL);
		i++;
	}
	return (tmp);
}

int	alloc_tab(t_game *game, bool first_alloc)
{
	char	**tmp;

	if (first_alloc == true)
	{
		game->map_data.map = ft_calloc(10, sizeof(char *));
		if (!game->map_data.map)
			return (ft_perror("Crash malloc in get_map()\n"), 1);
		game->map_data.heigth = 10;
		return (0);
	}
	else
	{
		tmp = ft_realloc(game->map_data.map, (game->map_data.heigth + 10) * \
						sizeof(char *), game->map_data.heigth * sizeof(char *));
		if (!tmp)
			return (ft_perror("Crash realloc in get_map()\n"), 1);
		game->map_data.map = tmp;
		game->map_data.heigth += 10;
	}
	return (0);
}
