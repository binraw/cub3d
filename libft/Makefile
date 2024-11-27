# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: florian <florian@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/26 07:56:54 by florian           #+#    #+#              #
#    Updated: 2024/11/27 19:27:34 by florian          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN		= \033[32m
YELLOW		= \033[33m
RESET		= \033[0m

LIB			= libft.a

SRC_DIR		= ./src
HDR_DIR		= ./hdr
BUILD_DIR	= .temp
OBJ_DIR		= $(BUILD_DIR)/.obj
DEP_DIR		= $(BUILD_DIR)/.dep

MODE		?= release

ifeq ($(MODE), debug)
CFLAGS	= -g3 -Wall -Wextra
else ifeq ($(MODE), release)
CFLAGS	= -o3 -Wall -Wextra -Werror
endif
DEPFLAGS	= -MMD -MT $(OBJ_DIR)/$*.o -MF $(DEP_DIR)/$*.d

SRC 		=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
				ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c \
				ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
				ft_putnbr_fd.c ft_putstr_fd.c ft_realloc.c ft_strchr.c ft_strdup.c \
				ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
				ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
				ft_substr.c ft_tolower.c ft_toupper.c ft_itoa.c ft_split.c \
				get_next_line.c get_next_line_utils.c

OBJ		= $(SRC:%.c=$(OBJ_DIR)/%.o)
DEP		= $(SRC:%.c=$(DEP_DIR)/%.d)

# --- CALL --- #
default	: all
all		: $(LIB)
debug:
	$(MAKE) MODE=debug

# --- ARCHIVE --- #
$(LIB) : $(OBJ)
	@echo "$(GREEN)--- compilation completed ---$(RESET)"
	ar -rcs $@ $^
	@echo "$(GREEN)"--- generated archive $(LIB) ---" $(RESET)"

# --- OBJECTS --- #
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c Makefile
	@mkdir -p $(dir $@) $(DEP_DIR)
	$(CC) $(CFLAGS) -I$(HDR_DIR) -c $< -o $@
	@$(CC) $(DEPFLAGS) -I$(HDR_DIR) -c $< && rm -f *.o

-include $(DEP)

# --- CLEAN MANAGEMENT --- #
clean :
	@rm -rf $(BUILD_DIR)
	@echo "$(YELLOW)--- removed temporary files ---$(RESET)"

fclean :
	@rm -rf $(BUILD_DIR) $(LIB)
	@echo "$(YELLOW)--- removed $(LIB) and temporary files ---$(RESET)"

re :
	$(MAKE) fclean
	$(MAKE) all

re_debug :
	$(MAKE) fclean
	$(MAKE) MODE=debug

.PHONY: all clean fclean re
