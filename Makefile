# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: florian <florian@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/26 13:30:05 by florian           #+#    #+#              #
#    Updated: 2024/11/27 19:44:36 by florian          ###   ########.fr        #
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
LIBFT		= $(DIR_LIBFT)/libft.a
MLX_LINUX	= $(DIR_MLX)/libmlx_Linux.a

#-------------------------# ==== SHELL COMANDS ==== #--------------------------#
RM		= rm -Rf
MD		= @mkdir -p

#------------------------------------------------------------------------------#
########################## DEFINE DIRECTORY PATHS ##############################
#---------------------# ==== LIBRARY DIRECTORIES ==== #------------------------#
DIR_MLX		= ./minilibx-linux
DIR_LIBFT	= ./libft

#-----------------------# ==== SOURCE CODE DIRECTORIES ==== #------------------#
HDR_DIR		= headers

DIR_SRC		= src
DIR_SHARED	= $(DIR_SRC)/shared
DIR_MAND	= $(DIR_SRC)/mandatory
DIR_BONUS	= $(DIR_SRC)/bonus


#---------------------# ==== TEMPORARY FILES DIRECTORIES ==== #----------------#
DIR_TEMP	= .tmp
DIR_OBJ		= $(DIR_TEMP)/.object
DIR_OBJ_B	= $(DIR_TEMP)/.object_b
DIR_DEP		= $(DIR_TEMP)/.dep
DIR_DEP_B	= $(DIR_TEMP)/.dep_b

#------------------------------------------------------------------------------#
######################## DEFINE COMPILATION ARGUMENTS ##########################
#----------------------# ==== LIBRARIES AND HEADERS ==== #---------------------#
LIBS_INC	= $(LIBFT) $(MLX_LINUX) -lXext -lX11 -lm
HEADERS_INC	= -I$(HDR_DIR) -I$(DIR_MLX) -I$(DIR_LIBFT)/hdr

#-----------------------# ==== COMPILATION FLAGS ==== #------------------------#
MODE		?= release

ifeq ($(MODE), debug)
	CFLAGS = -Wall -Wextra -g3
else ifeq ($(MODE), release)
	CFLAGS = -Wall -Wextra -Werror -O3
endif

DEPFLAGS	= -MMD -MT $(DIR_OBJ)/$*.o -MF $(DIR_DEP)/$*.d
DEPFLAGS_B	= -MMD -MT $(DIR_OBJ_B)/$*.o -MF $(DIR_DEP_B)/$*.d

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
OBJS			=	$(MANDATORY_FILES:%.c=$(DIR_OBJ)/%.o) \
					$(SHARED_FILE:%.c=$(DIR_OBJ)/%.o)
DEP				=	$(MANDATORY_FILES:%.c=$(DIR_DEP)/%.d) \
					$(SHARED_FILE:%.c=$(DIR_DEP)/%.d)

BONUS_OBJ		= 	$(SRC_BONUS:%.c=$(DIR_OBJ_B)/%.o) \
					$(SHARED_FILE:%.c=$(DIR_OBJ_B)/%.o)
DEP_B			=	$(SRC_BONUS:%.c=$(DIR_DEP_B)/%.d) \
					$(SHARED_FILE:%.c=$(DIR_DEP_B)/%.d)


#==============================================================================#
#                            COMPILATION MANDATORY                             #
#==============================================================================#
default	: all
all		: $(MLX_LINUX) $(LIBFT) $(NAME)
debug	:
	$(MAKE) MODE=debug

#--------------------# ==== COMPILATION OBJ - DEPS ==== #----------------------#
$(DIR_OBJ)/%.o: $(DIR_SHARED)/%.c Makefile
	@mkdir -p $(dir $@) $(DIR_DEP)
	$(CC) $(CFLAGS) $(HEADERS_INC) -c $< -o $@
	$(CC) $(DEPFLAGS) $(HEADERS_INC) -c $<
	@rm -f *.o

$(DIR_OBJ)/%.o: $(DIR_MAND)/%.c Makefile
	@mkdir -p $(dir $@) $(DIR_DEP)
	$(CC) $(CFLAGS) $(HEADERS_INC) -c $< -o $@
	$(CC) $(DEPFLAGS) $(HEADERS_INC) -c $<
	@rm -f *.o

#-------------------# ==== LINKING & BUILDING PROGRAM ==== #-------------------#
$(NAME): $(OBJS) $(LIBS_INC)
	@echo "$(GREEN)------------ compilation completed -------------$(RESET)"
	$(CC) -o $@ $^
	@echo "$(GREEN)************* your $(NAME) is READY **************$(RESET)"

-include $(DEP)

#==============================================================================#
#                              COMPILATION BONUS                               #
#==============================================================================#
bonus	: $(MLX_LINUX) $(LIBFT) $(B_NAME)
debug_bonus :
	$(MAKE) bonus MODE=debug

#--------------------# ==== COMPILATION OBJ - DEPS ==== #----------------------#
$(DIR_OBJ_B)/%.o: $(DIR_SHARED)/%.c Makefile
	$(MD) $(dir $@) $(DIR_DEP_B)
	$(CC) $(CFLAGS) $(HEADERS_INC) -c $< -o $@
	$(CC) $(DEPFLAGS_B) $(HEADERS_INC) -c $<
	@rm -f *.o

$(DIR_OBJ_B)/%.o: $(DIR_BONUS)/%.c Makefile
	$(MD) $(dir $@)  $(DIR_DEP_B)
	$(CC) $(CFLAGS) $(HEADERS_INC) -c $< -o $@
	$(CC) $(DEPFLAGS_B) $(HEADERS_INC) -c $<
	@rm -f *.o

#-------------------# ==== LINKING & BUILDING PROGRAM ==== #-------------------#
$(B_NAME): $(BONUS_OBJ) $(LIBS_INC)
	@echo "$(GREEN)-------------- compilation completed ---------------$(RESET)"
	$(CC) -o $@ $^
	@echo "$(GREEN)************* your $(B_NAME) is READY **************$(RESET)"

-include $(DEP_B)
#------------------------------------------------------------------------------#
########################## LIBRARY MAKEFILE CALL ###############################
#------------------------------------------------------------------------------#
$(MLX_LINUX): FORCE
	$(MAKE) -C $(DIR_MLX)
	@echo "$(GREEN)------- MLX compilation routine terminated ---------$(RESET)"

$(LIBFT): FORCE
ifeq ($(MODE), debug)
	$(MAKE) -C $(DIR_LIBFT) debug
else
	$(MAKE) -C $(DIR_LIBFT) all
endif

FORCE:

#------------------------------------------------------------------------------#
############################### CLEANING RULES #################################
#------------------------------------------------------------------------------#
clean:
	$(MAKE) -C $(DIR_LIBFT) clean & $(MAKE) -C $(DIR_MLX) clean
	$(RM) $(DIR_TEMP)
	@echo "$(YELLOW)--- removed temporary files ---$(RESET)"

fclean:
	$(MAKE) -C $(DIR_LIBFT) fclean & $(MAKE) -C $(DIR_MLX) clean
	$(RM) $(NAME) $(DIR_TEMP)
	@echo "$(YELLOW)--- removed $(NAME) and temporary files ---$(RESET)"

re:
	$(MAKE) fclean
	$(MAKE) all

re_debug:
	$(MAKE) fclean
	$(MAKE) MODE=debug

fclean_bonus:
	$(MAKE) -C $(DIR_LIBFT) fclean & $(MAKE) -C $(DIR_MLX) clean
	$(RM) $(B_NAME) $(DIR_TEMP)
	@echo "$(YELLOW)--- removed $(B_NAME) and temporary files ---$(RESET)"

re_debug_bonus:
	$(MAKE) fclean_bonus
	$(MAKE) bonus MODE=debug

re_bonus:
	$(MAKE) fclean_bonus
	$(MAKE) bonus

.PHONY: default all clean fclean re re_debug bonus fclean_bonus re_bonus re_debug_bonus FORCE
