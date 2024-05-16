# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/04 18:18:39 by bapasqui          #+#    #+#              #
#    Updated: 2024/05/16 15:36:10 by bapasqui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEBUG := 0

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
DEBUG_FLAGS := -fsanitize=address

ifdef DEBUG
    ifeq ($(DEBUG), 1)
        CFLAGS += -D DEBUG=$(DEBUG)
    else ifeq ($(DEBUG), 2)
        CFLAGS += $(DEBUG_FLAGS)
    endif
endif





SRCS	= src/main.c \
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
		  src/execution/signal.c \
		  src/execution/check.c \
		  src/utils/utils3.c \
		  src/utils/utils4.c \
		  src/utils/ft_is.c \
		  src/utils/parse_utils.c \
		  src/debug.c \
		  src/execution/exec_utils.c \
		  src/command_line/split_into_tokens.c \
		  src/command_line/cleaning_dlst_token.c \
		  src/command_line/input_reader.c \
		  src/command_line/tilde_expansion.c \
		  src/command_line/parameter_expansion.c \
		  src/command_line/varloc_creation.c \
		  src/command_line/create_command.c \
		  src/syntax_rules/ruler.c \
		  src/syntax_rules/keyword_rules.c \
		  src/syntax_rules/control_rules.c \
		  src/syntax_rules/redirect_rules.c \
		  src/dlst_parse/dlst_token_get.c \
		  src/dlst_parse/dlst_token_set.c \
		  src/dlst_parse/dlst_variable_get.c \
		  src/dlst_parse/dlst_variable_set.c \
		  src/dlst_parse/dlst_command_set.c \
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

$(NAME): init $(OBJS) 
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_TARGET) -lreadline

gdb: 
	gdb --tui ./$(NAME)

norm:
	@printf "\n$(PROJECT_NAME)[ Norm check : ]\n"
	@norminette $(SRCS) includes libft src | grep -v "Notice: GLOBAL_VAR_DETECTED"

norminette:
	@python3 -m pip install --upgrade pip setuptools
	@python3 -m pip install norminette
	@-norminette | grep -v "Notice: GLOBAL_VAR_DETECTED"
	
tester: all
	@-cd tester/minishell_tester/src/ && ./tester

clean:
	rm -rf $(OBJS_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	rm -rf tester/src/__pycache__
#make -C $(LIBFT_DIR) fclean
	rm -rf minishell-tester
	rm -rf outfile
	rm -rf infile
	echo "\033[41m$(NAME) cleaned\033[0m"

init:
	@echo ""
	@echo "\t\t$(BHYEL)┍━━━━━━━━━»•» 🌸  «•«━┑$(NC)"
	@echo "\t\t$(BHYEL) MINISHELL COMPILATION $(NC)"
	@echo "\t\t$(BHYEL)┕━»•» 🌸  «•«━━━━━━━━━┙$(NC)"
	@echo ""

re: fclean all

.PHONY: all clean fclean re norm checker
