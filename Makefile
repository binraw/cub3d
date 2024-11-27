# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/26 13:30:05 by florian           #+#    #+#              #
#    Updated: 2024/11/27 08:37:35 by fberthou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                              SETTING VARIABLES                               #
#==============================================================================#

GREEN		= \033[32m
YELLOW		= \033[33m
RESET		= \033[0m

#------------------------# ==== EXECUTABLE NAMES ==== #------------------------#
NAME	= cub3D
B_NAME	= cub3D_bonus

#------------------------# ==== STATIC LIBRAIRIES ==== #-----------------------#
LIBFT		= $(DIR_LIBFT)libft.a
MLX_LINUX	= $(DIR_MLX)libmlx_Linux.a

#-------------------------# ==== SHELL COMANDS ==== #--------------------------#
RM		= rm -Rf
MD		= @mkdir -p

#------------------------------------------------------------------------------#
########################## DEFINE DIRECTORY PATHS ##############################
#---------------------# ==== LIBRARY DIRECTORIES ==== #------------------------#
DIR_MLX		= ./minilibx-linux/
DIR_LIBFT	= ./libft/

#-----------------------# ==== SOURCE CODE DIRECTORIES ==== #------------------#
DIR_SRC		= src/
DIR_SHARED	= $(DIR_SRC)shared/
DIR_MAND	= $(DIR_SRC)mandatory/
DIR_BONUS	= $(DIR_SRC)bonus/

HDR_DIR		= headers/
HDR_MAND	= $(HDR_DIR)cub.h
HDR_BONUS	= $(HDR_DIR)cub_bonus.h

#---------------------# ==== TEMPORARY FILES DIRECTORIES ==== #----------------#
DIR_TEMP	= .tmp/
DIR_OBJ		= $(DIR_TEMP).object/
DIR_OBJ_B	= $(DIR_TEMP).object_b/
DIR_DEP		= $(DIR_TEMP).dep/
DIR_DEP_B	= $(DIR_TEMP).dep_b/

#------------------------------------------------------------------------------#
######################## DEFINE COMPILATION ARGUMENTS ##########################
#----------------------# ==== LIBRARIES AND HEADERS ==== #---------------------#
LIBS_INC	= $(LIBFT) $(MLX_LINUX) -lXext -lX11 -lm
HEADERS_INC	= -I$(HDR_DIR) -I$(DIR_MLX) -I$(DIR_LIBFT)hdr

#-----------------------# ==== COMPILATION FLAGS ==== #------------------------#
MODE		?= release

ifeq ($(MODE), debug)
CFLAGS		= -g3
else ifeq ($(MODE), release)
CFLAGS		= -Wall -Wextra -Werror -O3
endif

DEPFLAGS	= -MM -MT $*.c -MF

#------------------------------------------------------------------------------#
############################ DEFINE FILE VARIABLES #############################
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

BONUS_OBJ		= 	$(SRC_BONUS:%.c=$(DIR_OBJ_B)%.o) \
					$(SHARED_FILE:%.c=$(DIR_OBJ_B)%.o)


#==============================================================================#
#                            COMPILATION MANDATORY                             #
#==============================================================================#
default	: all
all		: $(MLX_LINUX) $(LIBFT) $(NAME)
debug	:
	$(MAKE) -j re_debug

#--------------------# ==== COMPILATION OBJ - DEPS ==== #----------------------#
$(DIR_OBJ)%.o: $(DIR_SHARED)%.c $(HDR_MAND) Makefile
	@mkdir -p $(dir $@) $(DIR_DEP)
	@$(CC) $(DEPFLAGS) $(DIR_DEP)$*.d $(HEADERS_INC) $<
	$(CC) $(CFLAGS) $(HEADERS_INC) -c $< -o $@

$(DIR_OBJ)%.o: $(DIR_MAND)%.c $(HDR_MAND) Makefile
	@mkdir -p $(dir $@) $(DIR_DEP)
	@$(CC) $(DEPFLAGS) $(DIR_DEP)$*.d $(HEADERS_INC) $<
	$(CC) $(CFLAGS) $(HEADERS_INC) -c $< -o $@

#-------------------# ==== LINKING & BUILDING PROGRAM ==== #-------------------#
$(NAME): $(OBJS) $(LIBS_INC)
	@echo "$(GREEN)------------ compilation completed -------------$(RESET)"
	$(CC) $(CFLAGS) -o $@ $^
	@echo "$(GREEN)************* your $(NAME) is READY **************$(RESET)"

#==============================================================================#
#                              COMPILATION BONUS                               #
#==============================================================================#
bonus	: $(MLX_LINUX) $(LIBFT) $(B_NAME)
debug_bonus :
	$(MAKE) -j re_debug_bonus

#--------------------# ==== COMPILATION OBJ - DEPS ==== #----------------------#
$(DIR_OBJ_B)%.o: $(DIR_SHARED)%.c $(HDR_BONUS) Makefile
	$(MD) $(dir $@)  $(DIR_DEP_B)
	@$(CC) $(DEPFLAGS) $(DIR_DEP_B)$*.d $(HEADERS_INC) $<
	$(CC) $(CFLAGS) $(HEADERS_INC) -c $< -o $@

$(DIR_OBJ_B)%.o: $(DIR_BONUS)%.c $(HDR_BONUS) Makefile
	$(MD) $(dir $@)  $(DIR_DEP_B)
	@$(CC) $(DEPFLAGS) $(DIR_DEP_B)$*.d $(HEADERS_INC) $<
	$(CC) $(CFLAGS) $(HEADERS_INC) -c $< -o $@

#-------------------# ==== LINKING & BUILDING PROGRAM ==== #-------------------#
$(B_NAME): $(BONUS_OBJ) $(LIBS_INC)
	@echo "$(GREEN)-------------- compilation completed ---------------$(RESET)"
	$(CC) $(CFLAGS) -o $@ $^
	@echo "$(GREEN)************* your $(B_NAME) is READY **************$(RESET)"

#------------------------------------------------------------------------------#
########################## LIBRARY MAKEFILE CALL ###############################
#------------------------------------------------------------------------------#
$(MLX_LINUX): FORCE
	@$(MAKE) -C $(DIR_MLX) -j all
	@echo "$(GREEN)------------- MLX compilation routine terminated ---------------$(RESET)"

$(LIBFT): FORCE
	$(MAKE) -C $(DIR_LIBFT) -j all

FORCE:

#------------------------------------------------------------------------------#
############################### CLEANING RULES #################################
#------------------------------------------------------------------------------#
clean:
	$(MAKE) -C $(DIR_LIBFT) clean
	$(MAKE) -C $(DIR_MLX) clean
	@$(RM) $(DIR_TEMP)
	@echo "$(YELLOW)--- removed temporary files ---$(RESET)"

fclean:
	$(MAKE) -C $(DIR_LIBFT) fclean
	$(MAKE) -C $(DIR_MLX) clean
	@$(RM) $(NAME) $(DIR_TEMP)
	@echo "$(YELLOW)--- removed $(NAME) and temporary files ---$(RESET)"

re:
	$(MAKE) -j fclean
	$(MAKE) -j all

re_debug:
	$(MAKE) -j fclean
	$(MAKE) -j MODE=debug

fclean_bonus:
	$(MAKE) -C $(DIR_LIBFT) fclean
	$(MAKE) -C $(DIR_MLX) clean
	@$(RM) $(B_NAME) $(DIR_TEMP)
	@echo "$(YELLOW)--- removed $(B_NAME) and temporary files ---$(RESET)"

re_debug_bonus:
	$(MAKE) -j fclean_bonus
	$(MAKE) -j bonus MODE=debug

re_bonus:
	$(MAKE) -j fclean_bonus
	$(MAKE) -j bonus

.PHONY: default all clean fclean re re_debug bonus fclean_bonus re_bonus re_debug_bonus FORCE
