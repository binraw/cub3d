NAME = cub3d
NAME_BONUS = 

SRCS_FILE = main.c get_next_line.c get_next_line_utils.c 
SRCS_FILE_BONUS= 

MINILIBDIR = ./minilibx-linux
CC = cc
MD = mkdir -p
CFLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

DIR_SRC = src/
DIR_OBJ = .object/
DIR_OBJ_BONUS = .object_BONUS/
DIR_BONUS = bonus/
LIBFT = ./libft/libft.a

OBJS = $(patsubst %.c, ${DIR_OBJ}%.o, ${SRCS_FILE})
SRCS = $(addprefix ${DIR_SRC},${SRCS_FILE})


$(shell mkdir -p ${DIR_OBJ})

RM = rm -Rf

all: ${LIBFT} ${NAME}

bonus: ${LIBFT} ${NAME_BONUS}

${NAME}: ${OBJS} ${LIBFT}
	$(MAKE) -C $(MINILIBDIR)
	$(CC) $(OBJS) ${LIBFT} -L$(MINILIBDIR) ${MLX_FLAGS} $(MINILIBDIR)/libmlx.a -o $(NAME)

${DIR_OBJ}%.o: ${DIR_SRC}%.c ${DIR_SRC}/get_next_line.h Makefile ${LIBFT}
	$(MD) $(shell dirname $@)
	@echo "Compiling $< to $@"
	$(CC) ${CFLAGS} -c $< -o $@

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