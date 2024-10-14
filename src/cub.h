/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 07:54:20 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/10/14 13:23:09 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../minilibx-linux/mlx.h"
# include "get_next_line.h"

typedef struct player
{
    
} player_s;


typedef struct game_s
{
    void    *mlx_ptr;
    void    *mlx_win;
    char    **map;
    char    *text_no;
    char    *text_so;
    char    *text_we;
    char    *text_ea;
    char    *text_f;
    char    *text_c;
    int     numb_line;
} game_s;


int init_value_texture_no(game_s *game, size_t y);
int init_value_texture_so(game_s *game, size_t y);
int init_value_texture_we(game_s *game, size_t y);
int init_value_texture_ea(game_s *game, size_t y);
int init_value_texture_f(game_s *game, size_t y);
int init_value_texture_c(game_s *game, size_t y);
int	count_line_maap(char *file);
void	alloc_lign(char *file, game_s *game);
void	read_maap(char *file, game_s *game);
int control_texture_value(game_s *game);
int init_all_texture(game_s *game);
#endif

