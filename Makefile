# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/02 08:10:39 by bel-amri          #+#    #+#              #
#    Updated: 2023/03/04 21:16:02 by bel-amri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=			cub3d
FLAGS=			#-Wall -Werror -Wextra
CC=				cc
HEADERS=		includes/header.h
SRC_DIR=		src
SRC_FILES=		main.c \
				src/minimap.c \
				src/objects.c \
				src/drawers.c

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
