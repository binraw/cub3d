/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truv <truv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 07:54:20 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/10/16 12:02:35 by truv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

    # include "../libft/libft.h"
    # include "../minilibx-linux/mlx.h"
    # include "../minilibx-linux/mlx_int.h"
    # include "../libft/get_next_line.h"
    # include <sys/stat.h>
    # include <stdbool.h>
    # include <stdlib.h>
    # include <stdio.h>
    # include <fcntl.h>

	# define USAGE "Need a filepath as argument"

    typedef struct console
    {
        void    *mlx_ptr;
        void    *win_ptr;
    } console_s;

    typedef struct player
    {
        bool player_no;
        bool player_so;
        bool player_we;
        bool player_ea; 
    } player_s;

    typedef struct game_s
    {
        char    **file;
        char    **map;
        char    *text_no;
        char    *text_so;
        char    *text_we;
        char    *text_ea;
        char    *text_f;
        char    *text_c;
        size_t     numb_line;
        int     num_line_map;
		console_s	console;
    } game_s;

	/* === init_console.c === */
	int	init_console(game_s *game);



    int     init_value_texture_no(game_s *game, size_t y);
    int     init_value_texture_so(game_s *game, size_t y);
    int     init_value_texture_we(game_s *game, size_t y);
    int     init_value_texture_ea(game_s *game, size_t y);
    int     init_value_texture_f(game_s *game, size_t y);
    int     init_value_texture_c(game_s *game, size_t y);
    int     count_line_maap(char *file);
    void	alloc_lign(char *file, game_s *game);
    void	read_file(char *file, game_s *game);
    int     control_texture_value(game_s *game);
    int     init_all_texture(game_s *game);
    int init_pixel_map(game_s *game, int y);

    int process_create_map(game_s *game, char *file);
    int    control_value_player(player_s *player, char *str);
    int init_pos_player(game_s *game, int y);
    int isclosed(game_s *game);
    int isclosed_column(game_s *game);
    int check_last_value(game_s *game, int y, size_t i);
	int	ft_perror(char *msg);

#endif

