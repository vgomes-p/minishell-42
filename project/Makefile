# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/13 16:31:58 by vgomes-p          #+#    #+#              #
#    Updated: 2025/02/13 01:37:33 by vgomes-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror -I $(H_DIR) -I $(LIBFT_DIR)
DEBUG_FLAGS	=	-g3 -fsanitize=address
RM			=	rm -rf
MAKEFLAGS	=	--silent

# path and files
H_SRCS		=	minishell.h
H_DIR		=	includes/
HEADER		=	$(addprefix $(H_DIR), $(H_SRCS))

MAIN_SRCS	=	main.c main_utils.c prompt.c
MAIN_DIR	=	codes/

TOKEN_PARSE_SRCS	=	token.c \
				token_utils_0.c token_utils_1.c token_utils_2.c \
				parse.c \
				parse_utils_0.c
TOKEN_PARSE_DIR	=	codes/token_and_parse/

BUILDIN_SRCS	=	bi_utils.c cd.c echo.c env.c exit.c pwd.c export.c unset.c
BUILDIN_DIR	=	codes/buildins/

PIPE_SRCS	=	
PIPE_DIR	=	codes/pipe/

EXEC_SRCS	=	exec_utils.c exec_buildins.c exec_externs.c
EXEC_DIR	=	codes/exec/

OBJ_DIR		=	build/
OBJ_M		=	$(addprefix $(OBJ_DIR), $(MAIN_SRCS:.c=.o) $(TOKEN_PARSE_SRCS:.c=.o) $(BUILDIN_SRCS:.c=.o) $(PIPE_SRCS:.c=.o) $(EXEC_SRCS:.c=.o))

MAIN		=	$(addprefix $(MAIN_DIR), $(MAIN_SRCS))
TOKEN_PARSE		=	$(addprefix $(TOKEN_PARSE_DIR), $(TOKEN_PARSE_SRCS))
BUILDIN		=	$(addprefix $(BUILDIN_DIR), $(BUILDIN_SRCS))
PIPE		=	$(addprefix $(PIPE_DIR), $(PIPE_SRCS))
EXEC		=	$(addprefix $(EXEC_DIR), $(EXEC_SRCS))

LIBFT_DIR	=	includes/libft/
LIBFT		=	$(LIBFT_DIR)libft.a

LIBMS_DIR	=	includes/libms/
LIBMS		=	$(LIBMS_DIR)libms.a

LIBFT_OBJ	=	$(wildcard $(LIBFT_DIR)*.o)
LIBMS_OBJ	=	$(wildcard $(LIBMS_DIR)*.o)

LFLAGS		=	-lreadline
TERMCAP		=	-ltermcap

# Colors
RESET		=	\033[0m
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

#Progress bar
TOTAL_FILES = $(words $(OBJ_M) $(LIBFT_OBJ) $(LIBMS_OBJ))
COMPLETED = 0

define update_progress
			@$(eval COMPLETED=$(shell echo $$(($(COMPLETED)+1))))
			@$(eval PERCENT=$(shell echo $$(($(COMPLETED)*100/$(TOTAL_FILES)))))
			@$(eval FILLED=$(shell echo $$(($(PERCENT)*20/100))))
			@$(eval EMPTY=$(shell echo $$((20-$(FILLED)))))
			@printf "\r"
			@printf "$(YELLOW) LOADING MINISHELL! $(RESET) "
			@printf "$(CYAN)["
			@for i in $$(seq 1 $(FILLED)); do printf "🟦"; done
			@for i in $$(seq 1 $(EMPTY)); do printf "  "; done
			@printf "] %d%%$(RESET)" $(PERCENT)
endef

-include	dependencies.mk

# Rules
$(OBJ_DIR)%.o: $(MAIN_DIR)%.c $(HEADER)
			@mkdir -p $(OBJ_DIR)
			$(CC) $(FLAGS) -c $< -o $@  2>/dev/null
			@$(call update_progress)

$(OBJ_DIR)%.o: $(TOKEN_PARSE_DIR)%.c $(HEADER)
			@mkdir -p $(OBJ_DIR)
			$(CC) $(FLAGS) -c $< -o $@  2>/dev/null
			@$(call update_progress)

$(OBJ_DIR)%.o: $(BUILDIN_DIR)%.c $(HEADER)
			@mkdir -p $(OBJ_DIR)
			$(CC) $(FLAGS) -c $< -o $@  2>/dev/null
			@$(call update_progress)

$(OBJ_DIR)%.o: $(PIPE_DIR)%.c $(HEADER)
			@mkdir -p $(OBJ_DIR)
			$(CC) $(FLAGS) -c $< -o $@  2>/dev/null
			@$(call update_progress)

$(OBJ_DIR)%.o: $(EXEC_DIR)%.c $(HEADER)
			@mkdir -p $(OBJ_DIR)
			$(CC) $(FLAGS) -c $< -o $@  2>/dev/null
			@$(call update_progress)

$(NAME): $(OBJ_M) $(LIBFT) $(LIBMS)
			$(CC) $(FLAGS) $(OBJ_M) $(LIBMS) $(LIBFT) $(LFLAGS) $(TERMCAP) -o $(NAME)
			@echo "\n$(GREEN)✅ Execution completed! ✅$(RESET)\n"
			@sleep 0.5
			@echo "$(CYAN)🎉 Minishell created 🎉\nNow you need to relax, it will be open soon!\n"
			@sleep 3
			@clear
			@./minishell

$(LIBFT):
			@make -C $(LIBFT_DIR)

$(LIBMS): $(LIBFT)
			@make -C $(LIBMS_DIR)

debug: $(OBJ_M)
			$(CC) $(FLAGS) $(DEBUG_FLAGS) $(OBJ_M) $(LIBFT) $(LIBMS) $(LFLAGS) $(TERMCAP) -o $(NAME)
			@echo "\n$(REPINK)Execution completed: $(NAME) created in debug mode!$(RESET)"

depend:
			@$(CC) -MM $(FLAGS) $(MAIN) $(TOKEN_PARSE) $(BUILDIN) $(PIPE) $(EXEC) | sed 's|^\(.*\)\.o:|$(OBJ_DIR)\1.o:|' > dependencies.mk
			@echo "\n$(REWHITE)Dependencies updated in dependencies.mk!$(RESET)"

all:		$(NAME)

clean:
			@$(RM) $(OBJ_M)
			@make clean -C $(LIBFT_DIR)
			@make clean -C $(LIBMS_DIR)


fclean: clean
			@clear
			@$(RM) $(NAME)
			@$(RM) dependencies.mk
			@$(RM) build/
			@make fclean -C $(LIBFT_DIR)
			@make fclean -C $(LIBMS_DIR)
			@echo "$(RERED)Execution completed: minishell was completely deleted!$(RESET)\n"
			@sleep 2
			@echo "$(PINK)Cleaning terminal!$(RESET)"
			@sleep 2
			@clear

re:			fclean all


.PHONY:		all clean fclean re depend