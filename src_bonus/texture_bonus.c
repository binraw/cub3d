/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:13:54 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/11/13 11:14:43 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static int	init_texture_no(game_s *game)
{
	game->img_data[0].img_ptr = mlx_xpm_file_to_image(game->console.mlx_ptr, \
							game->texture.text_no, &game->img_data[0].width, \
							&game->img_data[0].height);
	if (!game->img_data[0].img_ptr)
		return (ft_perror("Invalid texture north file\n"), 1);
	game->img_data[0].data = mlx_get_data_addr(game->img_data[0].img_ptr, \
							&game->img_data[0].bpp, &game->img_data[0].s_line, \
							&game->img_data[0].endian);
	if (!game->img_data[0].data)
		return (free_textures(game), ft_perror("Failed get north data\n"), 1);
	return (0);
}

static int	init_texture_so(game_s *game)
{
	game->img_data[1].img_ptr = mlx_xpm_file_to_image(game->console.mlx_ptr, \
							game->texture.text_so, &game->img_data[1].width, \
							&game->img_data[1].height);
	if (!game->img_data[1].img_ptr)
		return (ft_perror("Invalid texture south file\n"), 1);
	game->img_data[1].data = mlx_get_data_addr(game->img_data[1].img_ptr, \
							&game->img_data[1].bpp, &game->img_data[1].s_line, \
							&game->img_data[1].endian);
	if (!game->img_data[1].data)
		return (free_textures(game), ft_perror("Failed get south data\n"), 1);
	return (0);
}

static int	init_texture_we(game_s *game)
{
	game->img_data[2].img_ptr = mlx_xpm_file_to_image(game->console.mlx_ptr, \
							game->texture.text_we, &game->img_data[2].width, \
							&game->img_data[2].height);
	if (!game->img_data[2].img_ptr)
		return (ft_perror("Invalid texture west file\n"), 1);
	game->img_data[2].data = mlx_get_data_addr(game->img_data[2].img_ptr, \
							&game->img_data[2].bpp, &game->img_data[2].s_line, \
							&game->img_data[2].endian);
	if (!game->img_data[2].data)
		return (free_textures(game), ft_perror("Failed get west data\n"), 1);
	return (0);
}

static int	init_texture_ea(game_s *game)
{
	game->img_data[3].img_ptr = mlx_xpm_file_to_image(game->console.mlx_ptr, \
							game->texture.text_ea, &game->img_data[3].width, \
							&game->img_data[3].height);
	if (!game->img_data[3].img_ptr)
		return (ft_perror("Invalid texture east file\n"), 1);
	game->img_data[3].data = mlx_get_data_addr(game->img_data[3].img_ptr, \
							&game->img_data[3].bpp, &game->img_data[3].s_line, \
							&game->img_data[3].endian);
	if (!game->img_data[3].data)
		return (free_textures(game), ft_perror("Failed get east data\n"), 1);
	return (0);
}

int	load_texture(game_s *game)
{
	if (init_texture_no(game) || init_texture_so(game) || \
		init_texture_we(game) || init_texture_ea(game))
	{
		destroy_all(game);
		return (1);
	}
	return (0);
}
