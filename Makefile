# ==== PROG/LIB NAME ==== #
NAME	= cub3d
B_NAME	= cub3d_bonus
LIBFT	= $(DIR_LIBFT)libft.a
MLX		= $(DIR_MLX)libmlx_Linux.a

# ==== SHELL COMANDS ==== #
RM		= rm -Rf
MD		= @mkdir -p

# ==== DIRECTORIES PATHS ==== #
#	### *** LIBRAIRIES PATH *** ###
DIR_MLX		= ./minilibx-linux/
DIR_LIBFT	= ./libft/
#	### *** HEADER PATH *** ###
HDR_DIR		= headers/
#	### *** SOURCES PATH *** ###
DIR_SRC		= src/
DIR_MAIN	= $(DIR_SRC)main/
DIR_INIT	= $(DIR_SRC)init/
DIR_PARS	= $(DIR_SRC)parsing/
DIR_RAY		= $(DIR_SRC)raycasting/
DIR_OBJ		= .object/
DIR_OBJ_B	= .object_b/
#	### *** SOURCES BONUS PATH *** ###
DIR_B_SRC	= src_bonus/

# ==== COMPILATION TOOLS ==== #
LIB_FLAG	= -I$(DIR_LIBFT)hdr -I$(DIR_MLX)
MLX_FLAGS	= -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -lm
CFLAGS		= -g -I$(HDR_DIR) $(LIB_FLAG) #-Wall -Wextra -Werror

### === SOURCES FILES === ###
SRCS_FILE		=	$(DIR_MAIN)main.c $(DIR_MAIN)free_memory.c \
					\
					$(DIR_INIT)init_console.c $(DIR_INIT)hook.c \
					\
					$(DIR_PARS)parsing.c $(DIR_PARS)parsing_utils.c \
					$(DIR_PARS)init_map.c $(DIR_PARS)init_texture.c \
					$(DIR_PARS)valid_map.c \
					\
					$(DIR_RAY)raycaster.c $(DIR_RAY)utils_raycaster.c \
					$(DIR_RAY)texture.c  $(DIR_RAY)draw.c \
					$(DIR_RAY)move.c \

### === BONUS FILES === ###
SRC_BONUS	=	$(DIR_B_SRC)main_bonus.c $(DIR_B_SRC)free_memory_bonus.c \
				\
				$(DIR_B_SRC)init_console_bonus.c $(DIR_B_SRC)hook_bonus.c \
				$(DIR_B_SRC)hook_utils_bonus.c \
				\
				$(DIR_B_SRC)parsing_bonus.c $(DIR_B_SRC)parsing_utils_bonus.c \
				$(DIR_B_SRC)init_map_bonus.c $(DIR_B_SRC)init_texture_bonus.c \
				$(DIR_B_SRC)valid_map_bonus.c \
				\
				$(DIR_B_SRC)raycaster_bonus.c $(DIR_B_SRC)utils_raycaster_bonus.c \
				$(DIR_B_SRC)texture_bonus.c  $(DIR_B_SRC)draw_bonus.c \
				$(DIR_B_SRC)move_bonus.c \
				$(DIR_B_SRC)mini_map_bonus.c

### === OBJECTS === ###
OBJS		= $(SRCS_FILE:$(DIR_SRC)%.c=$(DIR_OBJ)%.o)
BONUS_OBJ	= $(SRC_BONUS:$(DIR_B_SRC)%.c=$(DIR_OBJ_B)%.o)

### === COMPILATION RULES === ###
default: all
all: $(MLX) $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $@ $^ -L$(DIR_MLX) $(MLX_FLAGS)
	@echo "**** CUBD3D READY ****"

bonus: $(BONUS_OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(B_NAME) $^ -L$(DIR_MLX) $(MLX_FLAGS)
	@echo "**** CUBD3D_BONUS READY ****"

$(DIR_OBJ)%.o: $(DIR_SRC)%.c $(HDR_DIR)*.h Makefile $(LIBFT)
	@echo "Compiling $< to $@"
	$(MD) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJ_B)%.o: $(DIR_B_SRC)%.c $(HDR_DIR)*.h Makefile $(LIBFT)
	@echo "Compiling bonus $< to $@"
	$(MD) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX): FORCE
	$(MAKE) -C $(DIR_MLX) all

$(LIBFT): FORCE
	$(MAKE) -C ./libft all

FORCE :

### === CLEANING RULES === ###
clean:
	$(MAKE) -C ./libft clean
	$(RM) $(DIR_OBJ)

fclean: clean
	$(MAKE) -C ./libft fclean
	$(RM) $(NAME)

re: fclean all

clean_bonus:
	$(MAKE) -C ./libft clean
	$(RM) $(DIR_OBJ_B)

fclean_bonus: clean_bonus
	$(MAKE) -C ./libft fclean
	$(RM) $(B_NAME)

re_bonus: fclean_bonus bonus

.PHONY: all clean fclean re clean_bonus fclean_bonus re_bonus FORCE
