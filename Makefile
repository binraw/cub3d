# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: florian <florian@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/26 13:30:05 by florian           #+#    #+#              #
#    Updated: 2024/11/27 21:15:13 by florian          ###   ########.fr        #
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
NAME_B	= cub3D_bonus

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
	CFLAGS = -O3 -Wall -Wextra -Werror
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
default: all

all: $(MLX_LINUX) $(LIBFT) $(NAME)
	@echo
	@echo "$(GREEN)***************** $(NAME) is READY *****************$(RESET)"
	@echo

debug:
	$(MAKE) MODE=debug
	@echo
	@echo "$(GREEN)************* $(NAME) is in debug mode *************$(RESET)"
	@echo

#--------------------# ==== COMPILATION OBJ - DEPS ==== #----------------------#
$(DIR_OBJ)/%.o: $(DIR_SHARED)/%.c Makefile
	@mkdir -p $(dir $@) $(DIR_DEP)
	$(CC) $(CFLAGS) $(HEADERS_INC) -c $< -o $@
	@$(CC) $(DEPFLAGS) $(HEADERS_INC) -c $<
	@rm -f *.o

$(DIR_OBJ)/%.o: $(DIR_MAND)/%.c Makefile
	@mkdir -p $(dir $@) $(DIR_DEP)
	$(CC) $(CFLAGS) $(HEADERS_INC) -c $< -o $@
	@$(CC) $(DEPFLAGS) $(HEADERS_INC) -c $<
	@rm -f *.o

#-------------------# ==== LINKING & BUILDING PROGRAM ==== #-------------------#
$(NAME): $(OBJS) $(LIBS_INC)
	@echo "$(GREEN)------------ compilation completed -------------$(RESET)"
	$(CC) -o $@ $^
	@echo "$(GREEN)----------- linking & building completed -----------$(RESET)"

-include $(DEP)

#==============================================================================#
#                              COMPILATION BONUS                               #
#==============================================================================#
bonus: $(MLX_LINUX) $(LIBFT) $(NAME_B)
	@echo
	@echo "$(GREEN)**************** $(NAME_B) is READY ****************$(RESET)"
	@echo

debug_bonus:
	$(MAKE) bonus MODE=debug
	@echo
	@echo "$(GREEN)************* $(NAME) is in debug mode *************$(RESET)"
	@echo

#--------------------# ==== COMPILATION OBJ - DEPS ==== #----------------------#
$(DIR_OBJ_B)/%.o: $(DIR_SHARED)/%.c Makefile
	$(MD) $(dir $@) $(DIR_DEP_B)
	$(CC) $(CFLAGS) $(HEADERS_INC) -c $< -o $@
	@$(CC) $(DEPFLAGS_B) $(HEADERS_INC) -c $<
	@rm -f *.o

$(DIR_OBJ_B)/%.o: $(DIR_BONUS)/%.c Makefile
	$(MD) $(dir $@)  $(DIR_DEP_B)
	$(CC) $(CFLAGS) $(HEADERS_INC) -c $< -o $@
	@$(CC) $(DEPFLAGS_B) $(HEADERS_INC) -c $<
	@rm -f *.o

#-------------------# ==== LINKING & BUILDING PROGRAM ==== #-------------------#
$(NAME_B): $(BONUS_OBJ) $(LIBS_INC)
	@echo "$(GREEN)-------------- compilation completed ---------------$(RESET)"
	$(CC) -o $@ $^
	@echo "$(GREEN)----------- linking & building completed -----------$(RESET)"

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
	@echo "$(GREEN)------- LIBFT compilation routine terminated -------$(RESET)"

FORCE:

#------------------------------------------------------------------------------#
############################# RECOMPILATION CALL ###############################
#------------------------------------------------------------------------------#
re:
	$(MAKE) fclean
	$(MAKE) -j all

re_debug:
	$(MAKE) fclean
	$(MAKE) -j MODE=debug

re_bonus:
	$(MAKE) fclean_bonus
	$(MAKE) -j bonus

re_debug_bonus:
	$(MAKE) fclean_bonus
	$(MAKE) -j bonus MODE=debug

#------------------------------------------------------------------------------#
############################### CLEANING RULES #################################
#------------------------------------------------------------------------------#
clean:
	$(MAKE) -C $(DIR_LIBFT) clean & $(MAKE) -C $(DIR_MLX) clean
	@$(RM) $(DIR_OBJ) $(DIR_DEP)
	@echo "$(YELLOW)--- removed $(NAME) temporary files ---$(RESET)"

fclean:
	$(MAKE) -C $(DIR_LIBFT) fclean & $(MAKE) -C $(DIR_MLX) clean
	@$(RM) $(NAME) $(DIR_TEMP)
	@echo "$(YELLOW)--- removed $(NAME) and temporary files ---$(RESET)"

clean_bonus:
	$(MAKE) -C $(DIR_LIBFT) clean & $(MAKE) -C $(DIR_MLX) clean
	@$(RM) $(DIR_OBJ_B) $(DIR_DEP_B)
	@echo "$(YELLOW)--- removed $(NAME_B) temporary files ---$(RESET)"

fclean_bonus:
	$(MAKE) -C $(DIR_LIBFT) fclean & $(MAKE) -C $(DIR_MLX) clean
	@$(RM) $(NAME_B) $(DIR_TEMP)
	@echo "$(YELLOW)--- removed $(NAME_B) and temporary files ---$(RESET)"

fclean_all:
	$(MAKE) -C $(DIR_LIBFT) fclean & $(MAKE) -C $(DIR_MLX) clean
	@$(RM) $(NAME) $(NAME_B) $(DIR_TEMP)
	@echo "$(YELLOW)--- removed all executables and temporary files ---$(RESET)"


.PHONY: default all debug re_debug \
		bonus bonus_debug re_bonus \
		clean fclean re fclean_bonus \
		fclean_all re_debug_bonus
