# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/04 18:18:39 by bapasqui          #+#    #+#              #
#    Updated: 2024/06/27 09:04:46 by bapasqui         ###   ########.fr        #
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
		  src/built-ins/cd_utils.c \
		  src/built-ins/env.c \
		  src/built-ins/export.c \
		  src/built-ins/export_utils.c \
		  src/built-ins/export_add.c \
		  src/built-ins/export_chk.c \
		  src/built-ins/exit.c \
		  src/built-ins/exit_utils.c \
		  src/built-ins/unset.c \
		  src/built-ins/pwd.c \
		  src/built-ins/heredoc.c \
		  src/built-ins/heredoc_utils.c \
		  src/built-ins/heredoc_child.c \
		  src/command_line/split_into_tokens.c \
		  src/command_line/create_redirection.c \
		  src/command_line/cleaning_dlst_token.c \
		  src/command_line/input_reader.c \
		  src/command_line/tilde_expansion.c \
		  src/command_line/parameter_expansion.c \
		  src/command_line/create_command.c \
		  src/command_line/parameter_exp_utils.c \
		  src/dlst/dlst_token_get.c \
		  src/dlst/dlst_token_set.c \
		  src/dlst/dlst_variable_get.c \
		  src/dlst/dlst_variable_set.c \
		  src/dlst/dlst_command_del.c \
		  src/dlst/dlst_command_insert.c \
		  src/dlst/dlst_command_get.c \
		  src/dlst/dlst_env_set.c \
		  src/dlst/dlst_env_get.c \
		  src/dlst/dlst_redir_get.c \
		  src/dlst/dlst_redir_set.c \
		  src/execution/child.c \
		  src/execution/child_utils.c \
		  src/execution/signal.c \
		  src/execution/check.c \
		  src/execution/exec_args.c	\
		  src/execution/exec_helpers.c \
		  src/execution/redirection.c \
		  src/execution/redirection_not_fork.c \
		  src/execution/exec_utils.c \
		  src/execution/exec.c \
		  src/parse/census_utils.c \
		  src/parse/cleaning_utils.c \
		  src/parse/token_type.c \
		  src/parse/init.c \
		  src/parse/init_array.c \
		  src/parse/organizer.c \
		  src/syntax_rules/ruler.c \
		  src/syntax_rules/control_rules.c \
		  src/syntax_rules/redirect_rules.c \
		  src/utils/utils_another.c \
		  src/utils/utils_get.c \
		  src/utils/free.c \
		  src/utils/utils_print.c \
		  src/utils/ft_is.c 

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
	
tester: all
	@-cd tester/minishell_tester/src/ && ./tester mandatory

builtins: all
	@-cd tester/minishell_tester/src/ && ./tester builtins

redirects: all
	@-cd tester/minishell_tester/src/ && ./tester redirects

syntax: all
	@-cd tester/minishell_tester/src/ && ./tester syntax

command: all
	@-cd tester/minishell_tester/src/ && ./tester command

var: all
	@-cd tester/minishell_tester/src/ && ./tester var

pipes: all
	@-cd tester/minishell_tester/src/ && ./tester pipes

vtester: all
	@-cd tester/minishell_tester/src/ && ./vtester mandatory

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