/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:09:11 by fberthou          #+#    #+#             */
/*   Updated: 2024/11/19 11:30:48 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static bool	not_dup_is_digit(char **buff, int *colors)
{
	size_t	i;
	size_t	y;

	i = 0;
	while (i < 3)
	{
		if (colors[i] != -1)
			return (ft_perror("A color is duplicated in file\n"), false);
		i++;
	}
	i = 0;
	y = 0;
	while (buff[i])
	{
		while (buff[i][y] && buff[i][y] != '\n')
		{
			if (ft_isdigit(buff[i][y]) == 0)
				return (ft_perror("Bad RGB value in file\n"), false);
			y++;
		}
		y = 0;
		i++;
	}
	return (true);
}

static int	fill_colors(char *buffer, int *colors, int tab_size)
{
	char	**tmp;
	int		i;

	i = 1;
	while (buffer[i] && buffer[i] == ' ')
		i++;
	tmp = ft_split(&buffer[i], ',');
	if (!tmp)
		return (ft_perror("crash malloc in fill_color\n"));
	while (tmp[tab_size])
		tab_size++;
	if (not_dup_is_digit(tmp, colors) == false)
		return (free_map(tmp, tab_size), 1);
	i = -1;
	while (tmp[++i] && tmp[i][0])
	{
		if (i == 3)
			return (ft_perror("Invalid colors format in file\n"));
		colors[i] = ft_atoi(tmp[i]);
		if (colors[i] < 0 || colors[i] > 255)
			return (free_map(tmp, tab_size), \
					ft_perror("Invalid colors value in file\n"));
	}
	return (free_map(tmp, tab_size), 0);
}

static int	fill_direction(char *buff_f, char **buff_t, t_game *game)
{
	size_t	i;

	i = 2;
	if (*buff_t != NULL)
		return (ft_perror("One direction field is duplicated\n"));
	format_line(&buff_f, NULL);
	while (buff_f[i] && (buff_f[i] == ' ' || buff_f[i] == '\t'))
		i++;
	*buff_t = ft_substr(buff_f, i, ft_strlen(buff_f) - i);
	if (!*buff_t)
		return (ft_perror("crash malloc in fill_direction\n"));
	game->texture.all_text += 1;
	return (0);
}

static int	line_analysis(t_game *game, char *buffer)
{
	if (buffer[0] == 'N' && buffer[1] == 'O')
		return (fill_direction(buffer, &game->texture.text_no, game));
	else if (buffer[0] == 'S' && buffer[1] == 'O')
		return (fill_direction(buffer, &game->texture.text_so, game));
	else if (buffer[0] == 'E' && buffer[1] == 'A')
		return (fill_direction(buffer, &game->texture.text_ea, game));
	else if (buffer[0] == 'W' && buffer[1] == 'E')
		return (fill_direction(buffer, &game->texture.text_we, game));
	else if (buffer[0] == 'F')
	{
		game->texture.all_text += 1;
		return (fill_colors(buffer, game->texture.f_color, 0));
	}
	else if (buffer[0] == 'C')
	{
		game->texture.all_text += 1;
		return (fill_colors(buffer, game->texture.c_color, 0));
	}
	else if (is_empty_line(buffer) == false)
		return (ft_perror("Textures and map description are mixed\n"), 1);
	return (0);
}

int	get_textures(t_game *game, const int fd)
{
	char	*buffer;

	buffer = "buf";
	while (buffer != NULL && game->texture.all_text != 6)
	{
		buffer = get_next_line(fd);
		if (!buffer)
			break ;
		if (line_analysis(game, &buffer[skip_spaces(buffer)]))
			return (free(buffer), 1);
		if (game->texture.all_text == 6)
		{
			free(buffer);
			break ;
		}
		free(buffer);
	}
	if (check_extension_xpm(game->texture.text_no)
		|| check_extension_xpm(game->texture.text_so)
		|| check_extension_xpm(game->texture.text_ea)
		|| check_extension_xpm(game->texture.text_we))
		return (1);
	return (check_txtr(game));
}
