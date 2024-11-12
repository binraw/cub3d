# ==== PROG/LIB NAME ==== #
NAME	= cub3d						# prog name
LIBFT	= $(DIR_LIBFT)libft.a		# path to archive librairie libft
MLX		= $(DIR_MLX)libmlx_Linux.a	# path to archive librairie mlx

# ==== SHELL COMANDS ==== #
RM		= rm -Rf
MD		= @mkdir -p

# ==== DIRECTORIES PATHS ==== #
### *** LIBRAIRIES PATH *** ###
DIR_MLX		= ./minilibx-linux/
DIR_LIBFT	= ./libft/
### *** HEADER PATH *** ###
HDR_DIR		= headers/
###	# *** SOURCES PATH *** ###
DIR_SRC		= src/
DIR_MAIN	= $(DIR_SRC)main/
DIR_INIT	= $(DIR_SRC)init/
DIR_PARS	= $(DIR_SRC)parsing/
DIR_RAY		= $(DIR_SRC)raycasting/
DIR_OBJ		= .object/

# ==== COMPILATION TOOLS ==== #
LIB_FLAG	= -I$(DIR_LIBFT)hdr -I$(DIR_MLX)
MLX_FLAGS	= -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -lm
CFLAGS		= -g -I$(HDR_DIR) $(LIB_FLAG) #-Wall -Wextra -Werror

### === SOURCES FILE === ###
SRCS_FILE		=	$(DIR_MAIN)main.c $(DIR_MAIN)free_memory.c $(DIR_MAIN)destroy.c\
					\
					$(DIR_INIT)init_console.c $(DIR_INIT)hook.c \
					\
					$(DIR_PARS)parsing.c $(DIR_PARS)parsing_utils.c $(DIR_PARS)utils_texture.c \
					$(DIR_PARS)init_map.c $(DIR_PARS)init_texture.c $(DIR_PARS)valid_map.c \
					\
					$(DIR_RAY)raycaster.c $(DIR_RAY)utils_raycaster.c \
					$(DIR_RAY)texture.c  $(DIR_RAY)draw.c \
					$(DIR_RAY)move.c $(DIR_RAY)utils_draw.c \
					$(DIR_RAY)mini_map.c

OBJS	= $(SRCS_FILE:$(DIR_SRC)%.c=$(DIR_OBJ)%.o)

default: all
all: $(MLX) $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $@ $^ -L$(DIR_MLX) $(MLX_FLAGS)
	@echo "**** CUBD3D READY ****"

$(DIR_OBJ)%.o: $(DIR_SRC)%.c $(HDR_DIR)*.h Makefile $(LIBFT)
	@echo "Compiling $< to $@"
	$(MD) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX): FORCE
	$(MAKE) -C $(DIR_MLX) all

$(LIBFT): FORCE
	$(MAKE) -C ./libft all

FORCE :

clean:
	$(MAKE) -C  ./libft clean
	$(RM) $(DIR_OBJ)

fclean: clean
	$(MAKE) -C  ./libft fclean
	$(RM) $(NAME)

re: fclean all

clean_bonus:
	$(RM) $(DIR_OBJ_BONUS)
	$(MAKE) -C ./libft clean

fclean_bonus: clean_bonus
	@rm -f $(NAME_BONUS)
	$(MAKE) -C ./libft fclean

re_bonus: fclean_bonus bonus

.PHONY: all clean fclean re clean_bonus fclean_bonus re_bonus FORCE
