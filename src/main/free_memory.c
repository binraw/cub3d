/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:01:20 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/11/13 11:21:36 by rtruvelo         ###   ########.fr       */
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
