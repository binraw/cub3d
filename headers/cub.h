
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

    /* ==== MACROS ==== */

    /* ** ERROR MESSAGES ** */
	# define USAGE	        "Need one filepath as argument\n"
    # define E_FILE_FORMAT	"A file format error is detected\n"
    # define E_MULTIPLAY    "Multiple player definition is forbidden\n"
    # define E_INVALID_CHAR "Invalid char in the map\n"
    # define E_EMPTYLINE    "Empty line in the map description is forbidden\n"


    /* ** PROG CONSTANTES ** */
	# define WIN_W		700	// largeur de la fenetre
	# define WIN_H		700	// hauteur de la fenetre
	# define NUM_RAYS	WIN_W	// nombre de rayon a tracer

	# define MLX_PTR	game->console.mlx_ptr
	# define WIN_PTR	game->console.win_ptr

	// tous les angles sont donnes en radian
	# define ANGLE_N	4.71238898		// == (3 * M_PI) * 0.5
	# define ANGLE_S	M_PI_2
	# define ANGLE_E	0
	# define ANGLE_W	M_PI
	# define ANGLE_FOV	1.047197551		// == M_PI / 3 == angle champ de vision player total
	# define FOV_2		0.5235987756	// == M_PI / 6 == ANGLE_FOV / 2

    // ces deux macros permettent de centrer la position du player dans sa case
    # define POS_Y(game)    (game)->plyr_data.pos_y - (TILE_S * 0.5)
    # define POS_X(game)    (game)->plyr_data.pos_x - (TILE_S * 0.5)

	# define ROT_SPEED	0.05
	# define MOV_SPEED	4
	# define TILE_S		64

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
		bool	colision_side;
	} ray_s;

    typedef struct player
    {
		double	pos_x;
		double	pos_y;
		double	dir_x;
		double	dir_y;
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
		int			height[4];
		int			width[4];
		void		*img_text_no;
		void		*img_text_so;
		void		*img_text_we;
		void		*img_text_ea;
	}	img_s;

	typedef struct draw
	{
		int	wall_h;
		int	wall_t;
		int	wall_b;
		int	txtr_x;
		int	color;
		int	i;
	}	draw_s;

    typedef struct game_s
    {
		console_s	console;
		texture_s	texture;
		player_s	plyr_data;
		map_s		map_data;
		ray_s		ray_data;
		img_s		img_data;
		draw_s		draw;
    } game_s;


	/* === Temporary function === */
	void	print_struct(game_s *game);
	void	print_player(game_s *game);
	void	print_ray(ray_s *ray);
	
	
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

	/* === init_map.c === */
	int		get_map(game_s *game, int fd);

	/* === valid_map.c === */
	int	check_map_validity(game_s *game);

	/* === init_texture.c === */
	int		get_textures(game_s *game, int fd);
	
	/* === texture.c === */
	void    load_texture(game_s *game);
	void    init_texture_no(game_s *game);
	void    init_texture_so(game_s *game);
	void    init_texture_we(game_s *game);
	void    init_texture_ea(game_s *game);

	/* === raycaster.c === */
	int	raycaster(game_s *game);

	/* === draw.c === */
	void	draw_wall_no_so(game_s *game, ray_s *ray, int column_index, int *end_x_y);
	void	draw_wall_ea_we(game_s *game, ray_s *ray, int column_index, int *end_x_y);


	// int	move(game_s *game , double move_x, double move_y);
	int loop_hook(game_s *game);
	// int update_movement(game_s *game);

#endif
