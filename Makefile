# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xlamiel- <xlamiel-@student.42barcelona.com>+#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/01 22:51:59 by xlamiel-          #+#    #+#              #
#    Updated: 2025/11/29 01:42:24 by xlamiel-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###############################################################################
# 🪄▶️ Command line
###############################################################################
#
#	Before:
#		libft -> make
#		minilibx-linux -> make
#
#cc -Wall -Wextra -Werror \
#	./src/*.c \
#	-I./include -I./minilibx-linux -I./libft/include \
#	-L./libft -lft \
#	-L./minilibx-linux -lmlx_Linux \
#	-L/usr/lib -lXext -lX11 -lm -lz \
#	-o fractol
#
###############################################################################
# 📦 Project Configuration
###############################################################################

NAME		:= fractol
SRC_DIR		:= src
OBJ_DIR		:= obj
DEP_DIR		:= dep
INCLUDE_DIR	:= include
MLX_DIR		:= ./minilibx-linux
MLX_LIB		:= $(MLX_DIR)/libmlx_Linux.a
LIBFT_DIR	:= ./libft
LIBFT		:= $(LIBFT_DIR)/libft.a

###############################################################################
# 🛠️ Tools & Commands
###############################################################################

CC			:= cc
RM			:= rm -f
MKDIR		:= mkdir -p

###############################################################################
# ⚙️ Compilation Flags
###############################################################################

#INCLUDES	:= -I$(INCLUDE_DIR) -I$(LIBFT_DIR)/include
#LDFLAGS		:= -L$(LIBFT_DIR)
#LDLIBS		:= -lft

CFLAGS		:= -Wall -Wextra -Werror
DEPFLAGS	:= -MMD -MP
INCLUDES	:= -I$(INCLUDE_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR)/include
MLX_FLAGS	:= -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
LDFLAGS		:= -L$(LIBFT_DIR)
LDLIBS		:= -lft

###############################################################################
# 🎨 Terminal Colors
###############################################################################

GREEN		:= \033[0;32m
RED			:= \033[0;31m
BOLD_CYAN	:= \033[1;36m
RESET		:= \033[0m

###############################################################################
# 📄 Source Files
###############################################################################

SRC			:= \
	$(SRC_DIR)/fractol.c \
	$(SRC_DIR)/fr_events.c \
	$(SRC_DIR)/fr_init.c \
	$(SRC_DIR)/fr_math_utils.c \
	$(SRC_DIR)/fr_render.c \
	$(SRC_DIR)/fr_aux.c \
	$(SRC_DIR)/fr_string_utils.c

###############################################################################
# 🔧 Derived File Lists
###############################################################################

OBJ			:= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
DEPS		:= $(patsubst $(SRC_DIR)/%.c,$(DEP_DIR)/%.d,$(SRC))

###############################################################################
# 🚀 Build Targets
###############################################################################

all: | $(OBJ_DIR) $(DEP_DIR)
all: $(LIBFT) $(MLX_LIB) $(NAME)

$(NAME): $(OBJ) $(MLX_LIB) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) $(LDFLAGS) $(LDLIBS) $(MLX_FLAGS) -o $@
	@echo "$(GREEN)✅ Executable '$@' created$(RESET)"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

###############################################################################
# 🧱 Object Compilation
###############################################################################

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile | $(OBJ_DIR) $(DEP_DIR)
	@$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@ -MF $(DEP_DIR)/$(notdir $*.d)

###############################################################################
# 📁 Directory Creation
###############################################################################

$(OBJ_DIR):
	@$(MKDIR) $@

$(DEP_DIR):
	@$(MKDIR) $@

###############################################################################
# 🧹 Cleaning Rules
###############################################################################

clean:
	@$(RM) -rf $(OBJ_DIR) $(DEP_DIR)
	@echo "$(RED)🧹 Object and dependency files removed$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)🧹 Executable '$(NAME)' removed$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(MLX_DIR) clean

re: fclean all

###############################################################################
# 🐞 Debug / Leak / Valgrind Builds (Optimized)
#
#	valgrind --leak-check=full ./executable params
#
#	Table info
#
#	Tool		Invalid access	Leaks		Speed
#------------------------------------------------
#	Valgrind	✅ yes			✅ yes		slow
#	ASan		✅ yes			❗ limit	fast
#	LSan		❌ no			✅ yes		fast
###############################################################################

debug: CFLAGS	:= $(CFLAGS) -g3
debug: re
	@echo "$(GREEN)🐞 Debug build created$(RESET)"

valgrind: CFLAGS	:= $(CFLAGS) -g3
valgrind: re
	@echo "$(GREEN)🐞 Build for Valgrind created$(RESET)"
	@echo "$(BOLD_CYAN)🐞 valgrind --leak-check=full ./$(NAME)$(RESET)"

###############################################################################
#
# Disabled by "minilibx_linux"
#
###############################################################################
#
#asan: CFLAGS	:= $(CFLAGS) -g3 -fsanitize=address
#asan: LDFLAGS	:= -fsanitize=address
#asan: re
#	@echo "$(GREEN)🐞 Build with AddressSanitizer created$(RESET)"
#
#lsan: CFLAGS	:= $(CFLAGS) -g3 -fsanitize=address,leak
#lsan: LDFLAGS	:= -fsanitize=address,leak
#lsan: re
#	@echo "$(GREEN)🐞 Build with LeakSanitizer created$(RESET)"
#
###############################################################################
# 📎 Dependency Inclusion
###############################################################################

#-include $(wildcard $(DEPS))
-include $(DEPS)

###############################################################################
# 📌 Phony Targets
###############################################################################

.PHONY: all clean fclean re debug
