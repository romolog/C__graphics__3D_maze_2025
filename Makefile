# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/06 15:14:57 by rponomar          #+#    #+#              #
#    Updated: 2025/04/24 23:20:18 by rponomar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# https://courses.cs.duke.edu/spring04/cps108/resources/makefiles/sample.html
# https://ideone.com/t94AOB
# https://best.openssf.org/Compiler-Hardening-Guides/Compiler-Options-Hardening-Guide-for-C-and-C++.html
# https://linuxhandbook.com/gcc-flags/
# https://caiorss.github.io/C-Cpp-Notes/compiler-flags-options.html
# -l<> : link shared library (lower case "L" = -l)
# -L<> : link external library (upper case "L" = -L)
# MAKEFILE_LIST: list of all parsed makefiles (pay attention to "include $(DEPS)" = list of makefiles)
# MAKECMDGOALS : list of goals, when you call make from bash: "make fclean" or "make re"
# $(warning Warning text without quotes) : Makefile:29: Warning text without quotes<new line>

MAKEFILE_DIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
ifneq (${MAKEFILE_DIR}, $(shell pwd))
INVALID_LOCATION := `make` must be called from within ${MAKEFILE_DIR} (or with option -C ${MAKEFILE_DIR})
$(error ERROR: $(INVALID_LOCATION))
endif

NAME = cub3D

IF_DEBUG := $(filter debug, $(MAKECMDGOALS))

ifeq ($(origin CC), default)
CC = cc
endif

ifeq (, $(filter debug, $(MAKECMDGOALS)))
CFLAGS ?= -O2
override CFLAGS += -DNDEBUG
else
override CFLAGS += -O0 -g
endif
FLAGS_WWW = -Wall -Wextra -Werror
override CFLAGS += $(FLAGS_WWW)

ifeq ($(origin RM), default)
RM = rm -rf
endif

ROOT_DIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
# $(info Makefile_List = $(MAKEFILE_LIST))
# $(info 1st word = $(firstword $(MAKEFILE_LIST)))
# $(info real path = $(realpath $(firstword $(MAKEFILE_LIST))))

CSRC_DIR = ./csrc/
# CSRC := $(notdir $(shell find ./csrc -iname "ft_cub3D_*.c"))
CSRC = \
	ft_cub3D_01_main.c						\
	ft_cub3D_02_err.c						\
	ft_cub3D_03_cleanup.c					\
	ft_cub3D_04_set_tracer.c				\
	ft_cub3D_07_set_map_raw.c				\
	ft_cub3D_09_set_map_isvalid.c			\
	ft_cub3D_08_set_map_transform_2darr.c	\
	ft_cub3D_06_set_map_raw.c				\
	ft_cub3D_10_set_map_isvalid_textures.c	\
	ft_cub3D_05_set_tracer.c				\
	ft_cub3D_11_set_player.c				\
	ft_cub3D_12_mlx_init.c					\
	ft_cub3D_13_set_textures.c				\
	ft_cub3D_14_calc_maze.c					\
	ft_cub3D_15_calc_cross.c				\
	ft_cub3D_16_calc_cross_xy.c				\
	ft_cub3D_17_calc_height_point.c			\
	ft_cub3D_18_calc_tex.c					\
	ft_cub3D_19_draw_maze.c					\
	ft_cub3D_20_events.c					\
	ft_cub3D_21_move_rotate.c				\
	ft_cub3D_22_utils_maloc.c				\
	ft_cub3D_23_utils_free.c				\
	ft_cub3D_24_utils_mix.c

ifeq (, $(IF_DEBUG))
COBJ_DIR ?= build/
else
override COBJ_DIR = debug/
endif
COBJ := $(addprefix $(COBJ_DIR), $(CSRC:.c=.o))

DEPS_DIR = ./deps/
DEPS = $(addprefix $(DEPS_DIR), $(CSRC:.c=.d))
NODEPS = clean fclean bonus

LIB_DIR_LIBFT = ./libs/libft/
LIB_DIR_MLX = ./libs/mlx42_paris/
LIB_DIRS = $(LIB_DIR_LIBFT) $(LIB_DIR_MLX)
define LIB_CLEAN =
$(MAKE) -C $(1) clean
endef

LIB_LIBFT = $(addprefix $(LIB_DIR_LIBFT), libft.a)
LIB_MLX	= $(addprefix $(LIB_DIR_MLX), libmlx_Linux.a)
LIBS = $(LIB_LIBFT) $(LIB_MLX)

override CPPFLAGS +=				\
	-I./incls						\
	-I$(LIB_DIR_LIBFT)				\
	$(addsuffix $(LIB_DIR_MLX), -I)

# -----------------------------------------------------------
# What flags should be passed to the linker
#   In other words, where should we look for libraries to link with - note,
#   you should never need to include compiler specific directories here
#   because each compiler already knows where to look for its system files.
# LDFLAGS         = -L. \
#                   -L$(COURSE_DIR) \
#                   -R $(LIB_DIR):$(COURSE_DIR)

# LDFLAGS ?= -L/home/rponomar/CUB3D/libs/libft
# override LDFLAGS +=					\
# 	-L.								\
# 	-L/usr/lib						\
	# -L$(LIB_DIR_LIBFT)				
# -L$(LIB_DIR_MLX)
# -----------------------------------------------------------

# -----------------------------------------------------------
# What libraries should be linked with.
# For example, -lm links with libm.so, the math library.
# If you make a library of your own, say, libscandir.a, you have to link it
# in by adding -lscandir here.
override LDLIBS += -lm -lXext -lX11 -lz
# -----------------------------------------------------------

TEST_DIR = ./tests/
TEST_FILES = $(wildcard $(TEST_DIR)*.test)
TLOG = $(TEST_FILES:.test=.tlog)

.PHONY: all
all: $(NAME)

# !!!
# IMPORTANT: first place O-files (COBJ) and only afterwards place libraries (LIBS)
# otherwise there would be a compilation error "undefined reference to ..."
$(NAME): check_Linux $(COBJ) $(LIB_MLX) $(LIB_LIBFT) Makefile
	@$(CC) $(CFLAGS) $(LDLIBS) $(LDFLAGS) $(COBJ) $(LIBS) -o $@
	@echo "$(NAME): compiled"

.PHONY: check_Linux
check_Linux :
ifneq ($(shell uname), Linux)
	$(error ERROR: Not Linux!)
endif

.PHONY: debug
debug: $(addprefix $(COBJ_DIR), $(NAME))

$(addprefix $(COBJ_DIR), $(NAME)) : $(COBJ) $(LIB_MLX) $(LIB_LIBFT) Makefile
	@$(CC) $(CFLAGS) $(LDLIBS) $(COBJ) $(LDFLAGS) $(LIBS) -o $@
	@echo "$(NAME): compiled in debug mode"

$(COBJ): $(COBJ_DIR)%.o: $(CSRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(DEPS): $(DEPS_DIR)%.d: $(CSRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) -E $(CPPFLAGS) $(CFLAGS) -c $< -MM -MT $(addprefix $(COBJ_DIR), $(<F:.c=.o)) > $@

ifeq (, $(filter $(NODEPS), $(MAKECMDGOALS)))
include $(DEPS)
endif

$(LIB_LIBFT): 
	$(MAKE) -C $(LIB_DIR_LIBFT)

$(LIB_MLX):
	$(MAKE) -C $(LIB_DIR_MLX)

.PHONY: clean
clean:
	@$(RM) $(addprefix ./build/, $(CSRC:.c=.o)) $(addprefix ./debug/, $(CSRC:.c=.o)) $(DEPS) $(TLOG)
	@$(foreach dir, $(LIB_DIRS), $(call $(LIB_CLEAN), dir))

.PHONY: fclean
fclean: clean
	@$(RM) ./build/$(NAME) ./debug/$(NAME)
	@$(RM) ./build ./debug ./deps

.PHONY: re
re: fclean all

.PHONY: bonus
bonus:
	$(info No bonus)

.PHONY: testrun
testrun: $(NAME)
	@chmod 744 runtest.sh
	@$(ROOT_DIR)/runtest.sh || true



# $(MAKE) -C $(DIR_LIBFT) clean
# $(MAKE) -C $(DIR_LIBFT) clean

# define LIB_MAKE =
# $(MAKE) -C $(1)
# endef
# LIB_DIRS = $(LIB_DIR_LIBFT) $(LIB_DIR_MLX)
# $(foreach dir, $(LIB_DIRS), $(call LIB_MAKE, dir))

# declare -A LIB_DICT=( \
# 	[$(LIB_LIBFT)]=$(LIB_DIR_LIBFT) \
# 	[$(LIB_MLX)]=$(LIB_DIR_MLX)); \
# for key in "$${!LIB_DICT[@]}"; \
# do $(call LIB_MAKE, $${LIB_DICT[$${key}]}); \
# done

# $(DIR_MLX):
# 	wget https://github.com/42Paris/minilibx-linux/archive/refs/heads/master.zip
# 	unzip master.zip -d libs
# 	rm -f master.zip
# 	mv ./libs/minilibx-linux-master ./libs/mlx42_paris	

# $(NAME): $(SRCS) $(HDRS) Makefile
# 	@$(CC) $(CFLAGS) $(SRCS) -o $@
# 	@echo "$(NAME): compiled"

# TEST = valgrind -q --leak-check=full ./$(NAME)