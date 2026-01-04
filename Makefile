# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/06 15:14:57 by rponomar          #+#    #+#              #
#    Updated: 2025/04/26 18:18:10 by rponomar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifneq ($(shell uname), Linux)
$(error ERROR: Not Linux!)
endif

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

# FLAGS_WWW = -Wall -Wextra -Werror
FLAGS_WWW = -Wall -Wextra
override CFLAGS += $(FLAGS_WWW)

ifeq ($(origin RM), default)
RM = rm -rf
endif

ROOT_DIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

CSRC_DIR = ./csrc/
CSRC = \
	ft_cub3D_01_main.c						\
	ft_cub3D_02_err.c						\
	ft_cub3D_03_cleanup.c					\
	ft_cub3D_04_set_tracer.c				\
	ft_cub3D_05_set_tracer.c				\
	ft_cub3D_06_set_map_raw.c				\
	ft_cub3D_07_set_map_raw.c				\
	ft_cub3D_08_set_map_raw.c				\
	ft_cub3D_09_set_map_transform_2darr.c	\
	ft_cub3D_10_set_map_isvalid.c			\
	ft_cub3D_11_set_map_isvalid_textures.c	\
	ft_cub3D_12_set_player.c				\
	ft_cub3D_13_mlx_init.c					\
	ft_cub3D_14_set_textures.c				\
	ft_cub3D_15_calc_maze.c					\
	ft_cub3D_16_calc_cross.c				\
	ft_cub3D_17_calc_cross_xy.c				\
	ft_cub3D_18_calc_height_point.c			\
	ft_cub3D_19_calc_tex.c					\
	ft_cub3D_20_draw_maze.c					\
	ft_cub3D_21_events.c					\
	ft_cub3D_22_move_rotate.c				\
	ft_cub3D_23_utils_maloc.c				\
	ft_cub3D_24_utils_free.c				\
	ft_cub3D_25_utils_mix.c


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

override LDLIBS += -lm -lXext -lX11 -lz

.PHONY: all
all: $(NAME)

$(NAME): $(COBJ) $(LIB_MLX) $(LIB_LIBFT) Makefile
	@$(CC)  $(CFLAGS) $(LDFLAGS) $(COBJ) $(LIBS) $(LDLIBS) -o $@
	@echo "$(NAME): compiled"

.PHONY: debug
debug: $(addprefix $(COBJ_DIR), $(NAME))

$(addprefix $(COBJ_DIR), $(NAME)) : $(COBJ) $(LIB_MLX) $(LIB_LIBFT) Makefile
	@$(CC) $(CFLAGS) $(LDFLAGS) $(COBJ) $(LIBS) $(LDLIBS) -o $@
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
	@$(RM) $(addprefix ./build/, $(CSRC:.c=.o)) $(addprefix ./debug/, $(CSRC:.c=.o)) $(DEPS)
	@$(foreach dir, $(LIB_DIRS), $(call $(LIB_CLEAN), dir))

.PHONY: fclean
fclean: clean
	@$(RM) $(NAME) ./debug/$(NAME)
	@$(RM) ./build ./debug ./deps

.PHONY: re
re: fclean all

.PHONY: bonus
bonus:
	$(info No bonus)
