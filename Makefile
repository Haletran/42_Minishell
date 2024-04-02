# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/04 18:18:39 by bapasqui          #+#    #+#              #
#    Updated: 2024/04/02 16:20:21 by bapasqui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


ifndef VERBOSE
MAKEFLAGS += --no-print-directory --silent
endif

NAME := minishell
CC := clang 
CFLAGS := -Wextra -Wall -Werror -g
DEBUG_FLAGS := -Wextra -Wall -Werror -g -fsanitize=address

SRCS	= src/main.c \
		  src/execution/redirections.c \
		  src/built-ins/echo.c \
		  src/built-ins/cd.c \
		  src/utils/utils.c \
		  src/utils/utils2.c \
		  src/parse/init.c \
		  src/built-ins/env.c \
		  src/built-ins/export.c \
		  src/built-ins/exit.c \
		  src/built-ins/unset.c \
		  src/built-ins/pwd.c \
		  src/built-ins/heredoc.c \
		  src/utils/free.c \
		  src/parse/parse.c \
		  src/execution/exec_and.c \
		  src/execution/exec_pipe.c \
		  src/execution/signal.c \
		  src/execution/check.c \
		  src/execution/exec.c

OBJS_DIR := obj
OBJS    := $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))
LIBFT_DIR = libft
LIBFT_TARGET = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@make -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_TARGET) -lreadline 
	echo "Compiling\033[1m\033[32m" $@ "\033[0m"
	echo "\033[42mSuccessfully compiled :)\033[0m"

norm:
	@printf "\n$(PROJECT_NAME)[ Norm check : ]\n"
	@norminette $(SRCS) includes libft src

tester: fclean all
	@if [ ! -d "minishell-tester" ]; then git clone https://github.com/RubenPin90/minishell-tester.git ; fi
	@cd minishell-tester && bash tester.sh

tester2: fclean
	@python3 -m pip install --upgrade pip setuptools
	@python3 -m pip install norminette
	@pip3 install -r tester/requirements.txt
	@python3 tester/src/__main__.py ./

clean:
	rm -rf $(OBJS_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	rm -rf tester/src/__pycache__
	make -C $(LIBFT_DIR) fclean
	rm -rf minishell-tester
	echo "\033[41m$(NAME) cleaned\033[0m"

re: fclean all

.PHONY: all clean fclean re norm checker
