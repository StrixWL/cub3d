# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/02 08:10:39 by bel-amri          #+#    #+#              #
#    Updated: 2023/03/21 17:57:28 by bel-amri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=			cub3d
FLAGS=			-Wall -Werror -Wextra
CC=				cc
HEADERS=		includes/header.h
SRC_DIR=		src
SRC_FILES=		main.c \
				src/init.c \
				src/parsing/parsing_functions.c \
				src/parsing/parsing_functions2.c \
				src/parsing/parsing_functions3.c \
				src/keys_handler.c \
				src/objects.c \
				src/raycasting.c \
				src/player_movement.c \
				src/draw_3d.c \
				src/intersections/v_intersections.c \
				src/intersections/h_intersections.c \
				src/parsing/get_next_line/get_next_line.c \
				src/parsing/get_next_line/get_next_line_utils.c \
				src/parsing/tools/ft_strcmp.c \
				src/parsing/tools/ft_strlen.c \
				src/parsing/tools/ft_strrchr.c \
				src/parsing/tools/ft_strncmp.c \
				src/parsing/tools/ft_atoi.c \
				src/parsing/tools/ft_split.c \
				src/parsing/parsing.c \
				src/parsing/check_all.c \
				src/parsing/check_all2.c \
				src/parsing/check_all3.c \
				src/parsing/check_all4.c \
				src/parsing/fill_file.c \
				src/parsing/fill_settings.c \
				src/parsing/fill_settings2.c \

OBJ_FILES=		$(SRC_FILES:.c=.o)


all: $(NAME)


$(NAME): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) -Imlx -Iincludes -c $< -o $@

norminette:
	@echo \\n\\n\\n\\n\\n & norminette ${SRC_DIR} ${INCLUDE_DIR}

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all
