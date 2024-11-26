# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: florian <florian@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/26 13:30:05 by florian           #+#    #+#              #
#    Updated: 2024/11/26 16:03:43 by florian          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                              SETTING VARIABLES                               #
#==============================================================================#

GREEN		= \033[32m
YELLOW		= \033[33m
RESET		= \033[0m

#------------------------# ==== EXECUTABLES NAME ==== #------------------------#
NAME	= cub3D
B_NAME	= cub3D_bonus

#-----------------------# ==== STATICS LIBRAIRIES ==== #-----------------------#
LIBFT	= $(DIR_LIBFT)libft.a
MLX		= $(DIR_MLX)libmlx_Linux.a

#-------------------------# ==== SHELL COMANDS ==== #--------------------------#
RM		= rm -Rf
MD		= @mkdir -p

#------------------------------------------------------------------------------#
########################## DEFINE DIRECTORIES PATHS ############################
#------------------------# ==== DIR LIBRAIRIES ==== #--------------------------#
DIR_MLX		= ./minilibx-linux/
DIR_LIBFT	= ./libft/

#-----------------------# ==== DIR SOURCE CODE ==== #--------------------------#
DIR_SRC		= src/
DIR_SHARED	= $(DIR_SRC)shared/
DIR_MAND	= $(DIR_SRC)mandatory/
DIR_BONUS	= $(DIR_SRC)bonus/

HDR_DIR		= headers/
HDR_MAND	= $(HDR_DIR)cub.h
HDR_BONUS	= $(HDR_DIR)cub_bonus.h

#---------------------# ==== DIR TEMPORARY FILES ==== #------------------------#
DIR_TEMP	= .tmp/
DIR_OBJ		= $(DIR_TEMP).object/
DIR_OBJ_B	= $(DIR_TEMP).object_b/
DIR_DEP		= $(DIR_TEMP).dep/
DIR_DEP_B	= $(DIR_TEMP).dep_b/

#------------------------------------------------------------------------------#
######################## DEFINE COMPILATION ARGUMENTS ##########################
#----------------------# ==== INC LIBS && HEADERS ==== #-----------------------#
LIBS_INC	= $(LIBFT) $(MLX) -lXext -lX11 -lm
HEADERS_INC	= -I$(HDR_DIR) -I$(DIR_MLX) -I$(DIR_LIBFT)hdr -I/usr/include/X11

#-----------------------# ==== COMPILATION FLAGS ==== #------------------------#
MODE		?= release
ifeq ($(MODE), debug)
CFLAGS		= -g3
else ifeq ($(MODE), release)
CFLAGS		= -Wall -Wextra -Werror -o3
endif

DEPFLAGS	= -MM -MT $(OBJ_DIR)/$*.c -MF

#------------------------------------------------------------------------------#
############################ DEFINE FILES VARIABLES ############################
#-------------------------# ==== SHARED FILES ==== #---------------------------#
SHARED_FILE		=	main.c free_memory.c destroy.c init_console.c parsing.c \
					parsing_utils.c init_map.c init_texture.c valid_map.c \
					utils_raycaster.c texture.c draw.c utils_draw.c \
					init_texture_utils.c utils.c

#------------------------# ==== MANDATORY FILES ==== #-------------------------#
MANDATORY_FILES	=	hook.c raycaster.c move.c

#--------------------------# ==== BONUS FILES ==== #---------------------------#
SRC_BONUS		=	hook_bonus.c hook_utils_bonus.c raycaster_bonus.c \
					move_bonus.c mini_map_bonus.c

#------------------------# ==== TEMPORARY FILES ==== #-------------------------#
OBJS			=	$(MANDATORY_FILES:%.c=$(DIR_OBJ)%.o) \
					$(SHARED_FILE:%.c=$(DIR_OBJ)%.o)
DEPS			=	$(OBJS:%.o=$(DIR_DEP)%.d)

BONUS_OBJ		= 	$(SRC_BONUS:%.c=$(DIR_OBJ_B)%.o) \
					$(SHARED_FILE:%.c=$(DIR_OBJ_B)%.o)
DEPS_B			= 	$(BONUS_OBJ:%.o=$(DIR_DEP_B)%.d)


#==============================================================================#
#                            COMPILATION MANDATORY                             #
#==============================================================================#
defaul	: all
all		: $(MLX) $(LIBFT) $(NAME)
debug	:
	$(MAKE) MODE=debug -C $(DIR_LIBFT)
	$(MAKE) MODE=debug

#--------------------# ==== COMPILATION OBJ - DEPS ==== #----------------------#
$(DIR_OBJ)%.o: $(DIR_SHARED)%.c $(HDR_MAND) Makefile
	@mkdir -p $(dir $@) $(DIR_DEP)
	@$(CC) $(DEPFLAGS) $(DIR_DEP)$*.d $(HEADERS_INC) $<
	$(CC) $(CFLAGS) $(HEADERS_INC) -c $< -o $@

$(DIR_OBJ)%.o: $(DIR_MAND)%.c $(HDR_MAND) Makefile
	@mkdir -p $(dir $@) $(DIR_DEP)
	@$(CC) $(DEPFLAGS) $(DIR_DEP)$*.d $(HEADERS_INC) $<
	$(CC) $(CFLAGS) $(HEADERS_INC) -c $< -o $@

#-------------------# ==== LINKING && BUILING PROG ==== #----------------------#
$(NAME): $(OBJS) $(LIBS_INC)
	@echo "$(GREEN)------------ compilation completed -------------$(RESET)"
	$(CC) $(CFLAGS) -o $@ $^
	@echo "$(GREEN)************* your $(NAME) is READY **************$(RESET)"

#==============================================================================#
#                              COMPILATION BONUS                               #
#==============================================================================#
bonus	: $(MLX) $(LIBFT) $(B_NAME)

#--------------------# ==== COMPILATION OBJ - DEPS ==== #----------------------#
$(DIR_OBJ_B)%.o: $(DIR_SHARED)%.c $(HDR_BONUS) Makefile
	$(MD) $(dir $@)  $(DIR_DEP)
	@$(CC) $(DEPFLAGS) $(DIR_DEP)$*.d $(HEADERS_INC) $<
	$(CC) $(CFLAGS) $(HEADERS_INC) -c $< -o $@

$(DIR_OBJ_B)%.o: $(DIR_BONUS)%.c $(HDR_BONUS) Makefile
	$(MD) $(dir $@)  $(DIR_DEP)s
	@$(CC) $(DEPFLAGS) $(DIR_DEP)$*.d $(HEADERS_INC) $<
	$(CC) $(CFLAGS) $(HEADERS_INC) -c $< -o $@

#-------------------# ==== LINKING && BUILING PROG ==== #----------------------#
$(B_NAME): $(BONUS_OBJ) $(LIBS_INC)
	@echo "$(GREEN)--------------  compilation completed  ---------------$(RESET)"
	$(CC) $(CFLAGS) -o $@ $^
	@echo "$(GREEN)************* your $(B_NAME) is READY **************$(RESET)"

#------------------------------------------------------------------------------#
########################## LIBRAIRIES MAKEFILE CALL ############################
#------------------------------------------------------------------------------#
$(MLX): FORCE
	$(MAKE) -C $(DIR_MLX) all

$(LIBFT): FORCE
	$(MAKE) -C $(DIR_LIBFT) all

-include $(DEPS)

FORCE:

#------------------------------------------------------------------------------#
############################### CLEANING RULES #################################
#------------------------------------------------------------------------------#
clean:
	$(MAKE) -C $(DIR_LIBFT) clean
	$(MAKE) -C $(DIR_MLX) clean
	$(RM) $(DIR_TEMP)

fclean:
	$(MAKE) -C $(DIR_LIBFT) fclean
	$(MAKE) -C $(DIR_MLX) clean
	$(RM) $(NAME) $(DIR_TEMP)

re:
	$(MAKE) fclean
	$(MAKE) all

re_debug:
	$(MAKE) fclean
	$(MAKE) debug

fclean_bonus:
	$(MAKE) -C $(DIR_LIBFT) fclean
	$(MAKE) -C $(DIR_MLX) clean
	$(RM) $(B_NAME) $(DIR_TEMP)

re_bonus:
	$(MAKE) fclean_bonus
	$(MAKE) bonus

.PHONY: all clean fclean re re_debug bonus fclean_bonus re_bonus FORCE
