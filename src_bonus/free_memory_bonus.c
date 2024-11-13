/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:21:59 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/11/13 10:23:46 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

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

void	free_ptrtab_map(char **tab, size_t len)
{
	size_t	i;

	i = 0;
	if (!tab)
		return ;
	while (i < len)
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
	free_ptrtab_map(game->map_data.map, game->map_data.heigth);
}
