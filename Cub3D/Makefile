TARGET = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

# --- MLX42 CONFIGURATION ---
MLX_PATH = ./MLX42
MLX_LIB  = $(MLX_PATH)/build/libmlx42.a
# Flags para Linux/WSL: Requiere GLFW y dependencias gráficas
MLX_FLAGS = -L$(MLX_PATH)/build -lmlx42 -lglfw -ldl -pthread -lm

SRCS = src/main.c \
	src/initialize.c \
	src/parse_main.c \
	src/parse_elements.c \
	src/validate_color.c \
	src/validate_identifiers.c \
	src/parse_map.c \
	src/flood_fill.c \
	src/file_reader.c \
	src/strings_operations.c \
	src/print_data.c \
	src/split.c \
	src/free.c \
	src/functions_mlx.c \
	src/gnl/get_next_line.c \
	src/gnl/get_next_line_utils.c

OBJ = $(SRCS:.c=.o)

INC = -I ./inc -I $(MLX_PATH)/include

all: $(MLX_LIB) $(TARGET)

# Regla para compilar la MLX42 usando CMake si no existe
$(MLX_LIB):
	@if [ ! -d "$(MLX_PATH)/build" ]; then \
		cmake $(MLX_PATH) -B $(MLX_PATH)/build; \
	fi
	@cmake --build $(MLX_PATH)/build -j4

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) -o $(TARGET)

%.o: %.c Makefile inc/cub3d.h inc/get_next_line.h
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ)
	@if [ -d "$(MLX_PATH)/build" ]; then rm -rf $(MLX_PATH)/build; fi

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
