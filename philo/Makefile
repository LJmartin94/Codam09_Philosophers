# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lindsay <lindsay@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2021/06/15 16:40:18 by lindsay       #+#    #+#                  #
#    Updated: 2021/09/29 15:24:09 by limartin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo

ROOT_DIR = ./

SRC_PATH = $(ROOT_DIR)srcs/

UTILS_PATH = $(SRC_PATH)utils/

INCL_PATH = $(ROOT_DIR)incl/

CC = gcc

#TODO remove sanitise flag when submitting
# CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
CFLAGS = -Wall -Wextra -Werror -pthread

HEADER_FILES = $(INCL_PATH)

#Source files mandatory part
SRC = $(SRC_PATH)main.c \
	$(SRC_PATH)input_management.c \
	$(SRC_PATH)setup_game.c \
	$(SRC_PATH)time.c \
	$(SRC_PATH)print.c \
	$(UTILS_PATH)conversions.c \
	$(UTILS_PATH)e_malloc.c \
	$(UTILS_PATH)strcmp.c \
	

#Object files
OBJ := ${SRC:%.c=%.o}

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS)
	@echo "$(NAME) compiled"

%.o: %.c $(HEADER_FILES)
	@$(CC) -o $@ -c $< $(CFLAGS) -O3 -I $(INCL_PATH)

bonus:
	@$(MAKE) all
	@echo "...but done ✨fancy✨"

clean:
	@rm -f $(OBJ)
	@echo "$(NAME) object files cleaned"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) fully cleaned"

re: fclean all

.PHONY: all bonus clean fclean re