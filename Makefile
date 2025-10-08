NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -g

# Directories
SRC_DIR = src
CORE_DIR = $(SRC_DIR)/core
PLAYER_DIR = $(SRC_DIR)/player
RENDER_DIR = $(SRC_DIR)/render
PARSE_DIR = $(SRC_DIR)/parsing
UTILS_DIR = $(SRC_DIR)/utils

# Source Files
SRCS =	main.c \
		$(CORE_DIR)/init.c \
		$(CORE_DIR)/hooks.c \
		$(CORE_DIR)/exit.c \
		$(PLAYER_DIR)/move.c \
		$(RENDER_DIR)/render.c \
		$(RENDER_DIR)/render2.c \
		$(RENDER_DIR)/render3.c \
		$(RENDER_DIR)/minimap.c \
		$(PARSE_DIR)/parse_line.c \
		$(PARSE_DIR)/parse_map.c \
		$(PARSE_DIR)/parse_texture.c \
		$(PARSE_DIR)/parse_color.c \
		$(PARSE_DIR)/map_validator.c \
		$(PARSE_DIR)/load_textures.c \
		$(UTILS_DIR)/get_next_line.c \
		$(UTILS_DIR)/ft_string.c \
		$(UTILS_DIR)/ft_trimspl.c \
		$(UTILS_DIR)/ft_list.c \
		$(UTILS_DIR)/ft_clean.c


OBJS = $(SRCS:.c=.o)

# MiniLibX Config
MLX_DIR = include/minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a

# Linker Flags
LDFLAGS = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm

# Rules
all: $(NAME)

$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(MLX_LIB):
	@make -sC $(MLX_DIR)

clean:
	rm -f $(OBJS)
	@make -sC $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus:

.PHONY: all clean fclean re bonus
