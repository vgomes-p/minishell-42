# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/13 16:31:58 by vgomes-p          #+#    #+#              #
#    Updated: 2025/01/14 12:59:34 by vgomes-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror -I $(H_DIR) -I $(LIBFT_DIR)
DEBUG_FLAGS	=	-g -fsanitize=address
RM			=	rm -rf

# path and files
H_SRCS		=	minishell.h
H_DIR		=	includes/
HEADER		=	$(addprefix $(H_DIR), $(H_SRCS))

MAPA_SRCS	=	ms_interwin_0.c ms_utils_0.c minishell.c
MAPA_DIR	=	codes/
OBJ_DIR		=	build/
OBJ_M		=	$(addprefix $(OBJ_DIR), $(MAPA_SRCS:.c=.o))

MAPA		=	$(addprefix $(MAPA_DIR), $(MAPA_SRCS))

LIBFT_DIR	=	includes/libft/
LIBFT		=	$(LIBFT_DIR)libft.a

LFLAGS		=	-lreadline
TERMCAP		=	-ltermcap

# Colors
DEFAULT		=	\033[0m
RED			=	\033[1;31m
CYAN		=	\033[1;36m
PINK		=	\033[1;35m
GREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
REWHITE		=	\033[1;7;97m
RECYAN		=	\033[1;7;36m
REPINK		=	\033[1;7;35m
RERED		=	\033[1;7;31m
REGREEN		=	\033[1;7;32m
REYELLOW	=	\033[1;7;33m

-include	dependencies.mk

# Rules
$(OBJ_DIR)%.o: $(MAPA_DIR)%.c $(HEADER)
			@mkdir -p $(OBJ_DIR)
			$(CC) $(FLAGS) -c $< -o $@
			

$(NAME): $(OBJ_M) $(LIBFT)
			$(CC) $(FLAGS) $(OBJ_M) $(LIBFT) $(LFLAGS) $(TERMCAP) -o $(NAME)
			@echo -e "$(REGREEN)Execution completed: $(NAME) created!$(DEFAULT)"

$(LIBFT):
			@make -C $(LIBFT_DIR)

debug: $(OBJ_M)
			$(CC) $(FLAGS) $(OBJ_M) $(LIBFT) $(LFLAGS) $(TERMCAP) -o $(NAME)
			@echo -e "$(REPINK)Execution completed: $(NAME) created in debug mode!$(DEFAULT)"

depend:
			@$(CC) -MM $(FLAGS) $(MAPA) > dependencies.mk
			@echo -e "$(REWHITE)Dependencies updated in dependencies.mk!$(DEFAULT)"

all:		$(NAME)

clean:
			@$(RM) $(OBJ_M)
			@make clean -C $(LIBFT_DIR)
			@echo -e "$(REYELLOW)Execution completed: minishell was deleted!$(DEFAULT)"

fclean: clean
			@$(RM) $(NAME)
			@$(RM) dependencies.mk
			@$(RM) build/
			@make fclean -C $(LIBFT_DIR)
			@echo -e "$(RERED)Execution completed: minishell was completely deleted!$(DEFAULT)"

re:			fclean all


.PHONY:		all clean fclean re depend