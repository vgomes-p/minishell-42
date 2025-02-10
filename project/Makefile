# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/13 16:31:58 by vgomes-p          #+#    #+#              #
#    Updated: 2025/02/10 18:40:27 by vgomes-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror -I $(H_DIR) -I $(LIBFT_DIR)
DEBUG_FLAGS	=	-g3 -fsanitize=address
RM			=	rm -rf

# path and files
H_SRCS		=	minishell.h
H_DIR		=	includes/
HEADER		=	$(addprefix $(H_DIR), $(H_SRCS))

MAIN_SRCS	=	main.c main_utils.c prompt.c
MAIN_DIR	=	codes/

TOKEN_SRCS	=	token0.c token1.c token_utils0.c token_utils1.c
TOKEN_DIR	=	codes/tokens-parse/

BUILDIN_SRCS	=	cd.c echo.c env.c exit.c pwd.c export.c export_utils.c unset.c
BUILDIN_DIR	=	codes/buildins/

PIPE_SRCS	=	
PIPE_DIR	=	codes/pipe/

EXEC_SRCS	=	exec_cmd.c
EXEC_DIR	=	codes/exec/

OBJ_DIR		=	build/
OBJ_M		=	$(addprefix $(OBJ_DIR), $(MAIN_SRCS:.c=.o) $(TOKEN_SRCS:.c=.o) $(BUILDIN_SRCS:.c=.o) $(PIPE_SRCS:.c=.o) $(EXEC_SRCS:.c=.o))

MAIN		=	$(addprefix $(MAIN_DIR), $(MAIN_SRCS))
TOKEN		=	$(addprefix $(TOKEN_DIR), $(TOKEN_SRCS))
BUILDIN		=	$(addprefix $(BUILDIN_DIR), $(BUILDIN_SRCS))
PIPE		=	$(addprefix $(PIPE_DIR), $(PIPE_SRCS))
EXEC		=	$(addprefix $(EXEC_DIR), $(EXEC_SRCS))

LIBFT_DIR	=	includes/libft/
LIBFT		=	$(LIBFT_DIR)libft.a

LIBMS_DIR	=	includes/libms/
LIBMS		=	$(LIBMS_DIR)libms.a

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
$(OBJ_DIR)%.o: $(MAIN_DIR)%.c $(HEADER)
			@mkdir -p $(OBJ_DIR)
			$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(TOKEN_DIR)%.c $(HEADER)
			@mkdir -p $(OBJ_DIR)
			$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(BUILDIN_DIR)%.c $(HEADER)
			@mkdir -p $(OBJ_DIR)
			$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(PIPE_DIR)%.c $(HEADER)
			@mkdir -p $(OBJ_DIR)
			$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(EXEC_DIR)%.c $(HEADER)
			@mkdir -p $(OBJ_DIR)
			$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ_M) $(LIBFT) $(LIBMS)
			$(CC) $(FLAGS) $(OBJ_M) $(LIBMS) $(LIBFT) $(LFLAGS) $(TERMCAP) -o $(NAME)
			@echo -e "$(REGREEN)Execution completed: $(NAME) created!$(DEFAULT)"

$(LIBFT):
			@make -C $(LIBFT_DIR)

$(LIBMS): $(LIBFT)
			@make -C $(LIBMS_DIR)

debug: $(OBJ_M)
			$(CC) $(FLAGS) $(DEBUG_FLAGS) $(OBJ_M) $(LIBFT) $(LIBMS) $(LFLAGS) $(TERMCAP) -o $(NAME)
			@echo -e "$(REPINK)Execution completed: $(NAME) created in debug mode!$(DEFAULT)"

depend:
			@$(CC) -MM $(FLAGS) $(MAIN) $(TOKEN) $(BUILDIN) $(PIPE) $(EXEC) | sed 's|^\(.*\)\.o:|$(OBJ_DIR)\1.o:|' > dependencies.mk
			@echo -e "$(REWHITE)Dependencies updated in dependencies.mk!$(DEFAULT)"

all:		$(NAME)

clean:
			@$(RM) $(OBJ_M)
			@make clean -C $(LIBFT_DIR)
			@make clean -C $(LIBMS_DIR)
			@echo -e "$(REYELLOW)Execution completed: minishell was deleted!$(DEFAULT)"

fclean: clean
			@$(RM) $(NAME)
			@$(RM) dependencies.mk
			@$(RM) build/
			@make fclean -C $(LIBFT_DIR)
			@make fclean -C $(LIBMS_DIR)
			@echo -e "$(RERED)Execution completed: minishell was completely deleted!$(DEFAULT)"

re:			fclean all


.PHONY:		all clean fclean re depend