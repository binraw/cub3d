
#ifndef CUB_H
# define CUB_H

    # include "libft.h"
    # include "get_next_line.h"
    # include "mlx.h"
    # include "mlx_int.h"
    # include <sys/stat.h>
    # include <stdbool.h>
    # include <stdlib.h>
    # include <stdio.h>
    # include <fcntl.h>
    # include <math.h>

    /* ==== STRUCTURES ==== */

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
		int		f_color[3];
		int		c_color[3];
		int     all_text;
	} texture_s ;

	typedef struct ray
	{
		double	angle;
		int		pos_x;
		int		pos_y;
		double	dir_x;
		double	dir_y;
		double	delta_x;
		double	delta_y;
		int		step_x;
		int		step_y;
		double	side_x;
		double	side_y;
		double	wall_dist;
		bool	colision_side; // 0 == ea we : 1 == no so
	} ray_s;

    typedef struct player
    {
		bool	write;
		double	pos_x;
		double	pos_y;
		double	dir_x;
		double	dir_y;
		double	plane_x;
		double	plane_y;
		double	camera_x;
		double	angle;
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
	} map_s;

	typedef struct img
	{
		int     height;
		int     width;
		void    *img_ptr;
        char    *data;
		int		bpp; // bits par pixel
		int		s_line; // taille de chaque ligne
		int		endian; // ordre de stockage
		int		index;
	}	img_s;

	typedef struct draw
	{
		int	wall_h;
		int	wall_t;
		int	wall_b;
		int	txtr_x;
		int	color;
		int	floor_c; // color floor value after bit_shift init in parsing init_textures
		int	ceiling_c; // color ceiling value after bit_shift init in parsing init_textures
		int	i;
	}	draw_s;

    typedef struct game_s
    {
		console_s	console;
		texture_s	texture;
		player_s	plyr_data;
		map_s		map_data;
		ray_s		ray_data;
		img_s		img_data[4]; // 0 = NORTH : 1 = SOUTH : 2 = WEST : 3 = EAST
		draw_s		draw;
    } game_s;

/* ==== CONSTANTES ==== */

    // ERROR MESSAGES //
	# define USAGE	        "Need one filepath as argument\n"
    # define E_FILE_FORMAT	"A file format error is detected\n"
    # define E_MULTIPLAY    "Multiple player definition is forbidden\n"
    # define E_INVALID_CHAR "Invalid char in the map\n"
    # define E_EMPTYLINE    "Empty line in the map description is forbidden\n"

    // WINDOW WIDTH HEIGTH //
	# define WIN_W		700	// largeur de la fenetre
	# define WIN_H		700	// hauteur de la fenetre


    // MLX PTR ACCESS //
	# define MLX_PTR	game->console.mlx_ptr
	# define WIN_PTR	game->console.win_ptr

	// PLAYER ORIENTATION //
	# define ANGLE_N	4.71238898		// == (3 * M_PI) * 0.5
	# define ANGLE_S	M_PI_2
	# define ANGLE_E	0
	# define ANGLE_W	M_PI

    // FIELD OF VIEW //
	# define ANGLE_FOV	1.047197551		// == M_PI / 3 == 60 degrees
	# define FOV_2		0.5235987756	// == M_PI / 6 == 30 degrees

    // MOVES SPEED //
	# define ROT_SPEED	0.1
	# define MOV_SPEED	10
	# define TILE_S		64

/* === PROTOTYPES === */

	/* === Temporary function === */
	void	print_struct(game_s *game);
	void	print_player(game_s *game);
	void	print_ray(ray_s *ray);
	void    print_constante(game_s *game);


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
	int	destroy_all(game_s *game);

	/* === parsing.c === */
	int		parsing(game_s *game, char *filepath);

	/* === parsing_utils.c === */
	bool	is_valid_char(char c);
	bool	is_empty_line(char *buffer);
	bool	is_player(char c);
	char	**duplicate_map(char **src, size_t nb_ptr);
	int		alloc_tab(game_s *game, bool first_alloc);

	/* === init_map.c === */
	int		get_map(game_s *game, int fd);

	/* === valid_map.c === */
	int		check_map_validity(game_s *game);

	/* === init_texture.c === */
	int		get_textures(game_s *game, int fd);

	/* === texture.c === */
	int    load_texture(game_s *game);

	/* === raycaster.c === */
	int		loop_hook(game_s *game);
	void	init_wall_dist(game_s *game, ray_s *ray, int *end_x_y);

	/* === utils_raycaster.c === */
	void	init_ray(ray_s *ray, game_s *game, int nb_ray);
	void	init_wall_dist(game_s *game, ray_s *ray, int *end_x_y);

	/* === move.c === */
	int		update_movement(game_s *game);

	/* === draw.c === */
	void	draw_wall_no_so(game_s *game, ray_s *ray, int column_index, int *end_x_y);
	void	draw_wall_ea_we(game_s *game, ray_s *ray, int column_index, int *end_x_y);


    /* === mini_map.c*/
    void    print_minimap(game_s *game, ray_s *ray);

	// int	move(game_s *game , double move_x, double move_y);
	// int update_movement(game_s *game);

#endif