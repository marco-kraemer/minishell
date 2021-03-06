# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/01 11:22:06 by maraurel          #+#    #+#              #
#    Updated: 2021/10/01 12:56:04 by jdanelon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_PATH = ./src/*

OBJ_PATH = ./obj

SRC = $(notdir $(wildcard ./src/*/*.c))

OBJ = $(addprefix $(OBJ_PATH)/, $(SRC:.c=.o))

CC = clang

FLAGS = -Wall -Wextra -Werror

all: $(NAME) $(OBJ)

$(NAME): $(OBJ)
	$(MAKE) -C libft
	$(CC) $(FLAGS) $(OBJ) -ltermcap -lreadline ./libft/libft.a -o $(NAME)

$(OBJ_PATH)/%.o:	$(SRC_PATH)/%.c
	$(CC) -g $(FLAGS) -c $< -o $@

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C libft

clean:
	@$(RM) $(OBJ_PATH)/*.o

re: fclean all

run: all
	@./$(NAME)

git:
	git add .
	git commit -m "Update"
	git push

install:
	sudo apt-get install libreadline-dev
