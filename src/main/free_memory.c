/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:57:54 by fberthou          #+#    #+#             */
/*   Updated: 2024/11/13 08:57:57 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_ptrtab(char **tab)
{
	size_t	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	if (tab)
		free(tab);
	return ;
}

void	free_textures(game_s *game)
{
	if (game->texture.text_no != NULL)
		free(game->texture.text_no);
	if (game->texture.text_so != NULL)
		free(game->texture.text_so);
	if (game->texture.text_we != NULL)
		free(game->texture.text_we);
	if (game->texture.text_ea != NULL)
		free(game->texture.text_ea);
	return ;
}

void	free_map_data(game_s *game)
{
	free_textures(game);
	free_ptrtab(game->map_data.map);
}

void	free_console(game_s *game)
{
	mlx_destroy_window(game->console.mlx_ptr, game->console.win_ptr);
	mlx_destroy_display(game->console.mlx_ptr);
	free(game->console.mlx_ptr);
	return ;
}

int	destroy_all(game_s *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->img_data[i].img_ptr)
			mlx_destroy_image(MLX_PTR, game->img_data[i++].img_ptr);
	}
	mlx_destroy_image(MLX_PTR, game->img.img_ptr);
	free_map_data(game);
	free_console(game);
	return (0);
}
