/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:21:59 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/11/13 13:55:29 by rtruvelo         ###   ########.fr       */
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

void	free_textures(t_game *game)
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

void	free_map_data(t_game *game)
{
	free_textures(game);
	free_ptrtab_map(game->map_data.map, game->map_data.heigth);
}
