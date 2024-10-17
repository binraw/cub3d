/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 07:54:20 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/10/17 09:25:14 by fberthou         ###   ########.fr       */
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
    # include <math.h>

    /* ==== MACROS ==== */
	# define USAGE		"Need a filepath as argument"
	# define MLX_PTR	game->console.mlx_ptr
	# define WIN_PTR	game->console.win_ptr
	# define WIN_W		1200	// largeur de la fenetre
	# define WIN_H		1200	// hauteur de la fenetre
	# define A_NORTH	3 * M_PI_2// angle north M_PI_2 == macro de math.h == PI/2
	# define A_SOUTH	M_PI_2	// angle south == PI / 2 
	# define A_EAST		0		// angle east
	# define A_WEST		M_PI	// angle west M_PI == macro de math.h == PI
	# define A_FOV		60		// angle champ de vision player
	# define TILE_S		game->map_data.tile_size

    /* ==== STRUCTURES  */
    typedef struct console
    {
		void	*mlx_ptr;
		void	*win_ptr;
    } console_s;

	typedef struct texture
	{
		char	*text_no;
		char	*text_so;
		char	*text_we;
		char	*text_ea;
		char	*text_f;
		char	*text_c;
		int		f_color;
		int		c_color;
	} texture_s ;

    typedef struct player
    {
		int		pos_x;
		int		pos_y;
		double	angle_fov;	// angle du premier rayon -> PI/2 - A_FOV/2
		double	orientation;// angle de vue initial du player -> 0 == east : PI == west : PI/2 == south : 3*(PI/2) == north
		double	rot_speed;	// vitesse de rotation joueur (entre 0 et 1) 
		double	mov_speed;	// vitesse de deplacement du joueur
		bool	move_up;
		bool	move_down;
		bool	move_right;
		bool	move_left;
		bool	rotate_r;
		bool	rotate_l;
    } player_s;

	typedef struct map
	{
        char	**map;
		size_t	width;
		size_t	heigth;
		int		tile_size; // == WIN_WIDTH / map_width
	} map_s;

    typedef struct game_s
    {
		console_s	console;
		texture_s	texture;
		map_s		map_data;
		player_s	plyr_data;
    } game_s;



	/* === init === */
	int		init_console(game_s *game);
	void	hook_management(game_s *game);

	/* === free_memory.c === */
	void	free_console(game_s *game);


    int     init_value_texture_no(game_s *game, size_t y);
    int     init_value_texture_so(game_s *game, size_t y);
    int     init_value_texture_we(game_s *game, size_t y);
    int     init_value_texture_ea(game_s *game, size_t y);
    int     init_value_texture_f(game_s *game, size_t y);
    int     init_value_texture_c(game_s *game, size_t y);
    int     count_line_maap(char *file);
    void	alloc_lign(char *file, game_s *game);
    void	read_maap(char *file, game_s *game);
    int     control_texture_value(game_s *game);
    int     init_all_texture(game_s *game);

    int process_create_map(game_s *game, char *file);
    int    control_value_player(player_s *player, char *str);
    int init_pos_player(game_s *game, int y);
    int isclosed(game_s *game, int x);
    int isclosed_column(game_s *game, int x);
    int check_last_value(game_s *game, int y, size_t i);
	int	ft_perror(char *msg);

#endif

