# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/04 18:18:39 by bapasqui          #+#    #+#              #
#    Updated: 2024/04/17 16:52:14 by bapasqui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


ifndef VERBOSE
MAKEFLAGS += --no-print-directory --silent
endif

RED				:= \033[0;31m
BRED			:= \033[1;31m
BLINK_GREEN		:= \033[5;32m
BGREEN			:= \033[1;32m
BHYEL			:= \033[1;93m
BOLD			:= \033[1m
NC				:= \033[0m

NAME := minishell
CC := clang
CFLAGS := -Wextra -Wall -Werror -gdwarf-4
DEBUG_FLAGS := -Wextra -Wall -Werror -gdwarf-4 -fsanitize=address

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
		  src/utils/lst_utils.c \
		  src/parse/parse.c \
		  src/execution/exec_pipe.c \
		  src/execution/signal.c \
		  src/execution/check.c \
		  src/utils/utils3.c \
		  src/debug.c \
		  src/utils/ft_is.c \
		  src/dlst_parse/dlst_token_get.c \
		  src/dlst_parse/dlst_token_set.c \
		  src/command_line/split_into_tokens.c \
		  src/dlst_parse/dlst_env_set.c \
		  src/dlst_parse/dlst_env_get.c \
		  src/execution/exec.c

DEBUG := 0
SRC_DIR := src
OBJS_DIR := obj
OBJS    := $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))
LIBFT_DIR = libft
LIBFT_TARGET = $(LIBFT_DIR)/libft.a

all: $(NAME)
	@echo "\n\t$(BGREEN)$(NAME) = COMPILATION FINISHED !$(NC)\n"

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)  && echo "$(BGREEN)[✔]$(NC)\tCompiling:\t$(BOLD)$(notdir $<)$(NC)"
	
$(LIBFT_TARGET):
	make -C $(LIBFT_DIR)

$(NAME): $(LIBFT_TARGET) init $(OBJS) 
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_TARGET) -lreadline

norm:
	@printf "\n$(PROJECT_NAME)[ Norm check : ]\n"
	@norminette $(SRCS) includes libft src | grep -v "Notice: GLOBAL_VAR_DETECTED"

norminette:
	@python3 -m pip install --upgrade pip setuptools
	@python3 -m pip install norminette
	@-norminette 
	
tester: all
	@-cd tester/minishell_tester/src && ./tester mandatory

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
	rm -rf outfile
	rm -rf infile
	echo "\033[41m$(NAME) cleaned\033[0m"

init:
	@echo ""
	@echo "\t\t$(BHYEL)┍━━━━━━━━━━━»•» 🌸  «•«━┑$(NC)"
	@echo "\t\t$(BHYEL) MINISHELL COMPILATION $(NC)"
	@echo "\t\t$(BHYEL)┕━»•» 🌸  «•«━━━━━━━━━━━┙$(NC)"
	@echo ""

re: fclean all

.PHONY: all clean fclean re norm checker
