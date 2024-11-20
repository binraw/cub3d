/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:13:51 by florian           #+#    #+#             */
/*   Updated: 2024/11/20 10:49:28 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_txtr(t_game *game)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (game->texture.c_color[i++] == -1)
			return (ft_perror("Invalid ceiling color in map description\n"));
	}
	i = 0;
	while (i < 3)
	{
		if (game->texture.f_color[i++] == -1)
			return (ft_perror("Invalid floor color in map description\n"));
	}
	game->draw.ceiling_c = (game->texture.c_color[0] << 16) | \
				(game->texture.c_color[1] << 8) | (game->texture.c_color[2]);
	game->draw.floor_c = (game->texture.f_color[0] << 16) | \
				(game->texture.f_color[1] << 8) | (game->texture.f_color[2]);
	return (0);
}

int	check_extension_xpm(char *str)
{
	size_t	i;

	i = ft_strlen(str);
	if (i < 4)
		return (ft_perror("Bad texture file extension\n"), 1);
	i--;
	if (str[i] != 'm' || str[i - 1] != 'p'
		|| str[i - 2] != 'x' || str[i - 3] != '.')
		return (ft_perror("Bad texture file extension\n"), 1);
	return (0);
}
