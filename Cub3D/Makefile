TARGET = cub3d

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

SRCS = src/main.c \
	src/initialize.c \
	src/parse_main.c \
	src/parse_elements.c \
	src/validate_color.c \
	src/validate_identifiers.c \
	src/parse_map.c \
	src/file_reader.c \
	src/strings_operations.c \
	src/print_data.c \
	src/split.c \
	src/free.c \
	src/gnl/get_next_line.c \
	src/gnl/get_next_line_utils.c

OBJ = $(SRCS:.c=.o)

INC     = -I ./inc

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

%.o: %.c Makefile cub3d.h get_next_line.h
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
