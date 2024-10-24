
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
	# define USAGE	        "Need one filepath as argument\n"
    # define E_FILE_FORMAT	"A file format error is detected\n"
    # define E_MULTIPLAY    "Multiple player definition is forbidden\n"
    # define E_INVALID_CHAR "Invalid char in the map\n"
    # define E_EMPTYLINE    "Empty line in the map description is forbidden\n"


    /* ** PROG CONSTANTES ** */
	# define WIN_W		1000	// largeur de la fenetre
	# define WIN_H		1000	// hauteur de la fenetre
	# define NUM_RAYS	WIN_W	// nombre de rayon a tracer

	# define MLX_PTR	game->console.mlx_ptr
	# define WIN_PTR	game->console.win_ptr

	// tous les angles sont donnes en radian
	# define ANGLE_N	M_PI_2				// PI/2, donc regarde en bas
	# define ANGLE_S	(3 * M_PI) * 0.5	// 3PI/2 donc regarde en haut
	# define ANGLE_E	0					// regarde a droite, point de depart
	# define ANGLE_W	M_PI				// PI donc regarde a gauche
	# define ANGLE_FOV	M_PI / 3			// angle champ de vision player total
	# define FOV_2		M_PI / 6			// ANGLE_FOV / 2

    // ces deux macros permettent de centrer la position du player dans sa case
	# define FOV_RAD	(FOV * game->plyr_data.angle) / 180
    # define POX_Y(game)    (game)->plyr_data.pos_y - (TILE_S * 0.5)
    # define POX_X(game)    (game)->plyr_data.pos_x - (TILE_S * 0.5)

	# define ROT_SPEED	0.05
	# define MOV_SPEED	0.25
	# define TILE_S		1

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

	typedef struct ray
	{
		double	angle;	// angle du premier rayon -> angle player - A_FOV/2
		double	pos_x;
		double	pos_y;
		double	dir_x;
		double	dir_y;
		double	plane_x;
		double	plane_y;
		double	delta_x;
		double	delta_y;
		double	step_x;
		double	step_y;
		double	side_x;
		double	side_y;
		bool	colision_side; // 0 == ligne vertical : 1 == ligne horizontale
		bool	hit_wall;
	} ray_s;

    typedef struct player
    {
		double	pos_x; // necessaire pour naviguer dans tab
		double	pos_y;
		double	dir_x;
		double	dir_y;
		double	angle;	// angle du premier rayon -> angle player - A_FOV/2
		double	initial_angle;
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
		bool	screen_change;
	} map_s;

    typedef struct game_s
    {
		console_s	console;
		texture_s	texture;
		map_s		map_data;
		player_s	plyr_data;
    } game_s;


	/* === Temporary function === */
	void	print_struct(game_s *game);
	void	print_player(game_s *game);

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
	void	init_player(game_s *game);
	int	raycaster(game_s *game);
	int	rotate(game_s *game);
	int	move(game_s *game , double move_x, double move_y);
	int loop_hook(game_s *game);
	int update_movement(game_s *game);
	int check_wall(double ray_x, double ray_y, game_s *game);
	void draw_wall(game_s *game, double ray_x, double ray_y, int column_index, double distance);
    int    control_value_player(player_s *player, char *str);
    // int init_pos_player(game_s *game, int y);
    // int isclosed(game_s *game, int x);
    // int isclosed_column(game_s *game, int x);
    // int check_last_value(game_s *game, int y, size_t i);
	int	ft_perror(char *msg);

#endif
