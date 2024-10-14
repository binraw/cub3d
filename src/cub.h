/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 07:54:20 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/10/14 10:42:02 by rtruvelo         ###   ########.fr       */
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

#endif

