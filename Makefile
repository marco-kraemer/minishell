# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/01 11:22:06 by maraurel          #+#    #+#              #
#    Updated: 2021/09/17 19:28:59 by jdanelon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_PATH = ./src

OBJ_PATH = ./obj

#SRC = $(notdir $(wildcard ./src/*.c))
SRC = $(notdir ./src/cd.c \
				./src/correct_args.c \
				./src/env.c \
				./src/export.c \
				./src/free.c \
				./src/help.c \
				./src/inout.c \
				./src/minishell.c \
				./src/readline.c \
				./src/run_shell.c \
				./src/sig_handlers.c \
				./src/split_args_extra.c \
				./src/split_args.c \
				./src/unset.c)

OBJ = $(addprefix $(OBJ_PATH)/, $(SRC:.c=.o))

CC = clang

FLAGS = -Wall -Wextra -Werror

all: $(NAME) $(OBJ)

$(NAME): lib $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -ltermcap -lreadline ./libft/libft.a -o $(NAME)

lib:
	@$(MAKE) -C libft

$(OBJ_PATH)/%.o:	$(SRC_PATH)/%.c
	@$(CC) -g $(FLAGS) -c $< -o $@

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


