# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lindsay <lindsay@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2021/06/15 16:40:18 by lindsay       #+#    #+#                  #
#    Updated: 2021/06/15 16:59:53 by lindsay       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo

ROOT_DIR = ./

SRC_PATH = $(ROOT_DIR)srcs/

INCL_PATH = $(ROOT_DIR)incl/

CC = gcc

#TODO remove sanitise flag when submitting
# CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
CFLAGS = -Wall -Wextra -Werror

HEADER_FILES = $(INCL_PATH)

#Source files mandatory part
SRC = $(SRC_PATH)main.c \
	$(SRC_PATH)input_management.c \
	

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