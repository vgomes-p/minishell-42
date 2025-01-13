# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/13 16:31:58 by vgomes-p          #+#    #+#              #
#    Updated: 2025/01/13 19:12:01 by vgomes-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror -I $(H_DIR) -I $(LIBFT_DIR)
RM			=	rm -rf

# path and files
H_SRCS		=	minishell.h
H_DIR		=	includes/
HEADER		=	$(addprefix $(H_DIR), $(H_SRCS))

MAPA_SRCS	=	ms_interwin_0.c ms_interwin_1.c ms_utils_0.c minishell.c
MAPA_DIR	=	codes/
OBJ_DIR		=	build/
OBJ_M		=	$(addprefix $(OBJ_DIR), $(MAPA_SRCS:.c=.o))

MAPA		=	$(addprefix $(MAPA_DIR), $(MAPA_SRCS))

LIBFT_DIR	=	includes/libft/
LIBFT		=	$(LIBFT_DIR)libft.a

LFLAGS		=	-lreadline

TERMCAP		=	-ltermcap

# Colors
RED  = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m

# Rules
$(OBJ_DIR)%.o: $(MAPA_DIR)%.c $(HEADER)
			@mkdir -p $(OBJ_DIR)
			$(CC) $(FLAGS) -c $< -o $@
			

$(NAME): $(OBJ_M) $(LIBFT)
			$(CC) $(FLAGS) $(OBJ_M) $(LIBFT) $(LFLAGS) $(TERMCAP) -o $(NAME)
			@echo -e "$(GREEN)Execution completed: $(NAME) created!$(DEFAULT)"

$(LIBFT):
			@make -C $(LIBFT_DIR)

all:		$(NAME)

clean:
			@$(RM) $(OBJ_M)
			@make clean -C $(LIBFT_DIR)
			@echo -e "$(YELLOW)execution completed!$(DEFAULT)"

fclean: clean
			@$(RM) $(NAME)
			@make fclean -C $(LIBFT_DIR)
			@echo -e "$(RED)all execution completed!$(DEFAULT)"

re:			fclean all

.PHONY:		all clean fclean re