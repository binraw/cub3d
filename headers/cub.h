/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:38:06 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/11/19 09:02:56 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct console
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_console;

typedef struct texture
{
	char	*text_no;
	char	*text_so;
	char	*text_we;
	char	*text_ea;
	int		f_color[3];
	int		c_color[3];
	int		all_text;
}	t_texture;

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
}	t_ray;

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
	int		rotate_m;
}	t_player;

typedef struct map
{
	char	**map;
	size_t	width;
	size_t	heigth;
}	t_map;

typedef struct img
{
	int		height;
	int		width;
	void	*img_ptr;
	char	*data;
	int		bpp;
	int		s_line;
	int		endian;
}	t_img_data;

typedef struct draw
{
	int	wall_h;
	int	wall_t;
	int	wall_b;
	int	floor_c;
	int	ceiling_c;
}	t_draw;

typedef struct t_game
{
	t_console	console;
	t_texture	texture;
	t_map		map_data;
	t_player	plyr_data;
	t_draw		draw;
	t_ray		ray_data;
	t_img_data	img_data[4];
	t_img_data	img;
}	t_game;

# define USAGE	        "Need one filepath as argument\n"
# define E_FILE_FORMAT	"A file format error is detected\n"
# define E_MULTIPLAY    "Multiple player definition is forbidden\n"
# define E_INVALID_CHAR "Invalid char in the map\n"
# define E_EMPTYLINE    "Empty line in the map description is forbidden\n"
# define RED        0Xc70404
# define WIN_W		700
# define WIN_H		700
# define ANGLE_N	4.71238898
# define ANGLE_S	M_PI_2
# define ANGLE_E	0
# define ANGLE_W	M_PI
# define ANGLE_FOV	1.047197551
# define FOV_2		0.5235987756
# define ROT_SPEED	0.03
# define MOV_SPEED	3
# define TILE_S		64
# define M_TILE_S    10

void	init_data_angle(t_game *game, float angle, int x, int y);
int		ft_perror(char *msg);
int		init_console(t_game *game);
void	hook_management(t_game *game);
int		init_console_mlx(t_game *game);
void	free_console(t_game *game);
void	free_textures(t_game *game);
void	free_map(char **tab, size_t len);
void	free_map_data(t_game *game);
int		destroy_all(t_game *game);
int		parsing(t_game *game, char *filepath);
bool	is_valid_char(char c);
bool	is_empty_line(char *buffer);
bool	is_player(char c);
char	**duplicate_map(char **src, size_t nb_ptr);
int		alloc_tab(t_game *game, bool first_alloc);
int		get_map(t_game *game, int fd);
int		format_line(char **line, size_t *length);
int		check_map_validity(t_game *game);
int		get_textures(t_game *game, int fd);
int		load_texture(t_game *game);
int		loop_hook(t_game *game);
void	init_ray(t_ray *ray, t_game *game, int nb_ray);
int		update_movement(t_game *game);
void	draw_column(t_game *game, t_ray *ray, int column_index	);
void	my_mlx_pixel_put(t_img_data *data, int x, int y, int color);
int		define_index(t_game *game, int nb, int index);
int		utils_color(t_game *game, t_ray *ray, int nb, int y_start);
void	print_minimap(t_game *game, t_ray *ray);
void	write_pixel_minimap(t_game *game, int start_x,
			int start_y, int curr_color);
void	destroy_bad_line(t_game *game, char	*buffer);
int		check_txtr(t_game *game);
int		define_texture_x(t_game *game, t_ray *ray, int nb);

#endif
