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
#	### *** SOURCES PATH *** ###
HDR_DIR		= headers/
DIR_SRC		= src/
DIR_SHARED	= $(DIR_SRC)shared/
DIR_MAND	= $(DIR_SRC)mandatory/
DIR_BONUS	= $(DIR_SRC)bonus/
DIR_OBJ		= .object/
DIR_OBJ_B	= .object_b/

# ==== COMPILATION TOOLS ==== #
LIB_FLAG	= -I$(DIR_LIBFT)hdr -I$(DIR_MLX)
MLX_FLAGS	= -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -lm
CFLAGS		= -I$(HDR_DIR) $(LIB_FLAG) -Wall -Wextra -Werror

### === SHARED PART === ###
SHARED_FILE		=	$(DIR_SHARED)main.c $(DIR_SHARED)free_memory.c $(DIR_SHARED)destroy.c \
					$(DIR_SHARED)init_console.c $(DIR_SHARED)parsing.c \
					$(DIR_SHARED)parsing_utils.c $(DIR_SHARED)init_map.c \
					$(DIR_SHARED)init_texture.c $(DIR_SHARED)valid_map.c \
					$(DIR_SHARED)utils_raycaster.c $(DIR_SHARED)texture.c \
					$(DIR_SHARED)draw.c $(DIR_SHARED)utils_draw.c \
					$(DIR_SHARED)init_texture_utils.c

### === MANDATORY PART === ###
SRCS_FILE		=	$(DIR_MAND)hook.c $(DIR_MAND)raycaster.c $(DIR_MAND)move.c

### === BONUS PART === ###
SRC_BONUS		=	$(DIR_BONUS)hook_bonus.c $(DIR_BONUS)hook_utils_bonus.c \
					$(DIR_BONUS)raycaster_bonus.c $(DIR_BONUS)move_bonus.c \
					$(DIR_BONUS)mini_map_bonus.c

### === OBJECTS === ###

OBJS			=	$(SRCS_FILE:$(DIR_MAND)%.c=$(DIR_OBJ)%.o) \
					$(SHARED_FILE:$(DIR_SHARED)%.c=$(DIR_OBJ)%.o)

BONUS_OBJ		= 	$(SRC_BONUS:$(DIR_BONUS)%.c=$(DIR_OBJ_B)%.o) \
					$(SHARED_FILE:$(DIR_SHARED)%.c=$(DIR_OBJ_B)%.o)

### === COMPILATION RULES === ###
default:	all
all:		$(MLX) $(LIBFT) $(NAME)
bonus:		$(MLX) $(LIBFT) $(B_NAME)

### === LINKER === ###
$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $@ $^ -L$(DIR_MLX) $(MLX_FLAGS)
	@echo "**** CUBD3D READY ****"

$(B_NAME): $(BONUS_OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(B_NAME) $^ -L$(DIR_MLX) $(MLX_FLAGS)
	@echo "**** CUBD3D_BONUS READY ****"

### === COMPILATION MANDATORY PART === ###
$(DIR_OBJ)%.o: $(DIR_SHARED)%.c $(HDR_DIR)cub.h Makefile $(LIBFT)
	@echo "Compiling $< to $@"
	$(MD) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJ)%.o: $(DIR_MAND)%.c $(HDR_DIR)cub.h Makefile $(LIBFT)
	@echo "Compiling $< to $@"
	$(MD) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

### === COMPILATION BONUS PART === ###
$(DIR_OBJ_B)%.o: $(DIR_SHARED)%.c $(HDR_DIR)cub_bonus.h Makefile $(LIBFT)
	@echo "Compiling shared $< for bonus to $@"
	$(MD) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJ_B)%.o: $(DIR_BONUS)%.c $(HDR_DIR)cub_bonus.h Makefile $(LIBFT)
	@echo "Compiling bonus $< to $@"
	$(MD) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

### === COMPILATION LIBRAIRIES === ###
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

.PHONY: all clean fclean re bonus clean_bonus fclean_bonus re_bonus FORCE
