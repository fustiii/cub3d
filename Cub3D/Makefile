TARGET = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# --- MLX42 CONFIGURATION ---
MLX_PATH = ./MLX42
MLX_LIB  = $(MLX_PATH)/build/libmlx42.a
# Flags para Linux/WSL: Requiere GLFW y dependencias gráficas
MLX_FLAGS = -L$(MLX_PATH)/build -lmlx42 -lglfw -ldl -pthread -lm

LIBFT_PATH = ./Libft/libft
LIBFT_LIB  = $(LIBFT_PATH)/libft.a
# -L = ruta (busca en...)
# -l = enlace (que se llame...)
LIBFT_FLAGS = -L$(LIBFT_PATH) -lft

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
	src/game_loop.c \
	src/textures.c \
	src/minimap_utils.c \
	src/draw_functions.c \
	src/handle_input.c \
	src/raycaster.c \
	src/raycaster_aux.c \
	src/draw_walls.c \
	src/exit.c \
	src/gnl/get_next_line.c \
	src/gnl/get_next_line_utils.c

OBJ = $(SRCS:.c=.o)

INC = -I ./inc -I $(MLX_PATH)/include

all: $(LIBFT_LIB) $(MLX_LIB) $(TARGET)

# --- GESTIÓN DE LA LIBRERÍA MLX42 ---
# Esta regla automatiza la preparación de la MLX42 como submódulo de Git:
# 1. Verifica si el submódulo está vacío (buscando CMakeLists.txt). 
#    Si lo está, ejecuta 'git submodule update --init' para descargarlo automáticamente.
# 2. Comprueba si existe la carpeta 'build'. Si no, lanza 'cmake' para configurar 
#    los archivos de compilación según el sistema operativo.
# 3. Compila la librería con 4 hilos (-j4) para generar el archivo .a final.
$(MLX_LIB):
	@if [ ! -f "$(MLX_PATH)/CMakeLists.txt" ]; then \
		echo "Submódulo no encontrado. Inicializando..."; \
		git submodule update --init --recursive; \
	fi
	@if [ ! -d "$(MLX_PATH)/build" ]; then \
		cmake $(MLX_PATH) -B $(MLX_PATH)/build; \
	fi
	@cmake --build $(MLX_PATH)/build -j4

$(LIBFT_LIB):
	@if [ ! -f "$(LIBFT_PATH)/ft_atoi.c" ]; then \
		echo "Submódulo no encontrado. Inicializando..."; \
		git submodule update --init --recursive; \
	fi
	@make -C $(LIBFT_PATH)

# Regla de compilacion general
# Junta archivos procesados y los junta para crear ejecutable final
# gcc -Wall -Wextra archivo1.o ... -lmlx ... -o mi_programa
# Le paso _FLAGS en vez de _LIB porque el sistema estándar de enlace de librerías en C.
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $(TARGET)

# Crea los .o a partir de los .c
%.o: %.c Makefile inc/cub3d.h inc/get_next_line.h
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ)
	@make -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(TARGET)
	@make -C $(LIBFT_PATH) fclean

clean_mlx:
	@if [ -d "$(MLX_PATH)/build" ]; then rm -rf $(MLX_PATH)/build; fi

clean_all: fclean clean_mlx

re: clean_all all

.PHONY: all clean fclean clean_mlx clean_all re
