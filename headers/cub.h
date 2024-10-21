/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 07:54:20 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/10/21 13:48:18 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

    # include "../libft/hdr/libft.h"
    # include "../minilibx-linux/mlx.h"
    # include "../minilibx-linux/mlx_int.h"
    # include "../libft/hdr/get_next_line.h"
    # include <sys/stat.h>
    # include <stdbool.h>
    # include <stdlib.h>
    # include <stdio.h>
    # include <fcntl.h>
    # include <math.h>

    /* ==== MACROS ==== */

    /* ** ERROR MESSAGES ** */
	# define USAGE	        "Need a filepath as argument\n"
    # define E_FILE_FORMAT	"A file format error is detected\n"
    # define E_MULTIPLAY    "Multiple player definition is forbidden\n"
    # define E_INVALID_CHAR "Invalid char in the map\n"
    # define E_EMPTYLINE    "Empty line in the map description is forbidden\n"


    /* ** PROG CONSTANTES ** */
	# define WIN_W	700	// largeur de la fenetre
	# define WIN_H	700	// hauteur de la fenetre

	# define MLX_PTR	game->console.mlx_ptr
	# define WIN_PTR	game->console.win_ptr

	# define ANGLE_N	3 * M_PI_2// angle north M_PI_2 == macro de math.h == PI/2
	# define ANGLE_S	M_PI_2	// angle south == PI / 2
	# define ANGLE_E	0		// angle east
	# define ANGLE_W	M_PI	// angle west M_PI == macro de math.h == PI
	# define FOV		60		// angle champ de vision player
	# define NUM_RAYS   WIN_W		// nombre de rayon a tracer

	# define ROT_SPEED	0.5
	# define MOV_SPEED	2
	# define TILE_S		5

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
		int		f_color[3];
		int		c_color[3];
		int     all_text;
	} texture_s ;

    typedef struct player
    {
		double	pos_x;
		double	pos_y;
		double	dir_x;
		double	dir_y;
		double	angle;	// angle du premier rayon -> PI/2 - A_FOV/2
		bool	move_up;
		double orientation;
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
		bool	screen_change;
	} map_s;

    typedef struct game_s
    {
		console_s	console;
		texture_s	texture;
		map_s		map_data;
		player_s	plyr_data;
    } game_s;


	/* === main.c === */
	int		ft_perror(char *msg);

	/* === init_console.c === */
	int		init_console(game_s *game);
	void	hook_management(game_s *game);

	/* === free_memory.c === */
	void	free_console(game_s *game);
	void	free_textures(game_s *game);
	void	free_ptrtab(char **tab);
	void	free_map_data(game_s *game);

	/* === parsing.c === */
	int		parsing(game_s *game, char *filepath);
	
	/* === parsing_utils.c === */
	bool	is_valid_char(char c);
	bool	is_empty_line(char *buffer);
	bool	is_player(char c);
	char	**duplicate_map(char **src, size_t nb_ptr);
	int		alloc_tab(game_s *game, bool first_alloc);
	
	/* === init_texture.c === */
	int		get_textures(game_s *game, int fd);
	
	/* === init_map.c === */
	int		get_map(game_s *game, int fd);

	/* === valid_map.c === */
	int	check_map_validity(game_s *game);

	

    int		init_pixel_map(game_s *game, int y);
	char	**dup_map_pixel(game_s *game, int y);
    // int		control_value_player(player_s *player, char *str);
	int		value_player(game_s *game, char c);

	int	raycaster(game_s *game);
	int	rotate(game_s *game);
	int	move(game_s *game , double move_x, double move_y);
	int loop_hook(game_s *game);
	int update_movement(game_s *game);
	int check_wall(double ray_x, double ray_y, game_s *game);
	void draw_wall(game_s *game, double ray_x, double ray_y, int column_index);
    int    control_value_player(player_s *player, char *str);
    // int init_pos_player(game_s *game, int y);
    // int isclosed(game_s *game, int x);
    // int isclosed_column(game_s *game, int x);
    // int check_last_value(game_s *game, int y, size_t i);
	int	ft_perror(char *msg);

#endif
