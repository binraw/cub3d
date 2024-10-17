NAME	= cub3d
#NAME_BONUS = 
RM		= rm -Rf
MD		= mkdir -p

# ==== DIRECTORIES PATHS ==== # 
MINILIBDIR	= ./minilibx-linux
HDR_DIR		= headers/
DIR_SRC		= src/
DIR_INIT	= $(DIR_SRC)init/
DIR_OBJ		= .object/
#DIR_BONUS = bonus/
#DIR_OBJ_BONUS = .object_BONUS/

# ==== COMPILATION TOOLS ==== #
CC			= cc
CFLAGS		= -g # -Wall -Wextra -Werror
MLX_FLAGS	= -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
LIBFT		= ./libft/libft.a

# SRC
SRCS_FILE		=	main.c  \
					init_console.c hook.c \
				 	 free_memory.c \
					raycaster.c
#SRCS_FILE_BONUS	= 

OBJS = $(patsubst %.c, ${DIR_OBJ}%.o, ${SRCS_FILE})
SRCS = $(addprefix ${DIR_SRC},${SRCS_FILE})

$(shell mkdir -p ${DIR_OBJ})

all: ${LIBFT} ${NAME}

#bonus: ${LIBFT} ${NAME_BONUS}

${NAME}: ${OBJS} ${LIBFT}
	$(MAKE) -C $(MINILIBDIR)
	$(CC) $(OBJS) ${LIBFT} -L$(MINILIBDIR) ${MLX_FLAGS} $(MINILIBDIR)/libmlx.a -o $(NAME)

${DIR_OBJ}%.o: ${DIR_SRC}%.c ${HDR_DIR}*.h Makefile ${LIBFT}
	$(MD) $(shell dirname $@)
	@echo "Compiling $< to $@"
	$(CC) ${CFLAGS} -I$(HDR_DIR) -c $< -o $@

${LIBFT}: 
	$(MAKE) -C ./libft all

clean:
	$(MAKE) -C  ./libft clean
	$(RM) ${DIR_OBJ}

fclean: clean
	$(MAKE) -C  ./libft fclean
	$(RM) ${NAME}

re: fclean all

clean_bonus:
	$(RM) ${DIR_OBJ_BONUS}
	$(MAKE) -C ./libft clean

fclean_bonus: clean_bonus
	@rm -f ${NAME_BONUS}
	$(MAKE) -C ./libft fclean

re_bonus: fclean_bonus bonus

.PHONY: all clean fclean re clean_bonus fclean_bonus re_bonus