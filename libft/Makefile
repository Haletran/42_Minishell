# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/31 11:10:06 by ygaiffie          #+#    #+#              #
#    Updated: 2024/04/02 22:33:26 by bapasqui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef VERBOSE
MAKEFLAGS += --no-print-directory --silent
endif

SHELL			:=	/bin/bash

RED				:= \033[0;31m
BRED			:= \033[1;31m
BLINK_GREEN		:= \033[5;32m
BGREEN			:= \033[1;32m
BHYEL			:= \033[1;93m
BOLD			:= \033[1m
NC				:= \033[0m

SRC_DIR 		:=	./src/
OBJ_DIR 		:=	./obj/

CC 				:= 	clang
CFLAGS 			:= 	-Wall -Werror -Wextra


SRCS			:= 	$(shell find ./src -iname "*.c")
OBJS			:= 	$(sort $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o))
MAIN_SRC		:=	main.c
MAIN_OBJ		:=	$(OBJ_DIR)main.o

NAME 			:= 	libft.a
HEADERS			:=	-I libft.h

all: init $(NAME)
	@echo -e "\t$(BLINK_GREEN)$(NAME) = COMPILATION FINISHED !$(NC)"
	@echo -e "$(BOLD)$(NAME)$(NC) is located in $(BOLD)$(shell find . -iname "$(NAME)")$(NC) !\n"
	
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && echo -e "$(BGREEN)[✔]$(NC)\tCompiling:\t$(BOLD)$(notdir $<)$(NC)"


$(NAME): $(OBJS)
	@ar rcs -o $@ $^ && echo -e "$(BGREEN)[✔]$(NC)\tArchiving:\t$(BOLD)$@\n"

dummy: $(MAIN_SRC)
	@$(CC) $(CFLAGS) $< -o $@ $(NAME) && echo -e "$(BGREEN)[✔]$(NC)\tLinking Exe:\t$(BOLD)$@"
	@echo -e "\t$(BLINK_BGREEN)$@ = COMPILATION FINISHED !$(NC)"
	@echo -e "$(BOLD)$@$(NC) is located in $(BOLD)$(shell find . -iname "$@")$(NC) !"

clean:
	@rm -fr $(OBJS) $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME) dummy
	
re: 
	@$(MAKE) fclean
	@$(MAKE) all

init:
	@echo -e ""
	@echo -e "\t\t$(BHYEL)┍━━━━━━━━━━━»•» 🌸 «•«━┑$(NC)"
	@echo -e "\t\t$(BHYEL) LIBFT MAKE COMPILATION $(NC)"
	@echo -e "\t\t$(BHYEL)┕━»•» 🌸 «•«━━━━━━━━━━━┙$(NC)"
	@echo -e ""
	@mkdir -p $(OBJ_DIR)
	
.PHONY: clean fclean all re init