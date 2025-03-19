# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/13 16:31:58 by vgomes-p          #+#    #+#              #
#    Updated: 2025/03/19 17:57:54 by vgomes-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	minishell
CC					=	cc
FLAGS				=	-Wall -Wextra -Werror -I $(H_DIR) -I $(LIBFT_DIR)
RM					=	rm -rf
MAKEFLAGS			=	--silent

# path and files
H_SRCS				=	minishell.h
H_DIR				=	includes/
HEADER				=	$(addprefix $(H_DIR), $(H_SRCS))

GENERAL_SRCS		=	utils.c all_free_0.c all_free_1.c
GENERAL_DIR			=	codes/utils/

MAIN_SRCS			=	main.c prompt.c prompt_utils.c
MAIN_DIR			=	codes/main/

TOKEN_PARSE_SRCS	=	token.c \
						token_utils_0.c token_utils_1.c token_utils_2.c \
						expand.c \
						remove_quote.c \
						parse.c \
						syntax.c
TOKEN_PARSE_DIR		=	codes/token_and_parse/

BUILTIN_SRCS		=	bi_utils.c bi_utils1.c cd.c echo.c env.c exit.c pwd.c export.c unset.c
BUILTIN_DIR			=	codes/builtins/

REDIR_SRCS			=	redirect.c \
						heredoc.c heredoc_utils.c heredoc_utils1.c
REDIR_DIR			=	codes/redir/

EXEC_SRCS			=	cmd_path.c  exec_family.c exec_builtins.c exec_externs.c init_exec.c\
						exec_utils_0.c exec_utils_1.c exec_utils_2.c is_utils.c family_utils.c
EXEC_DIR			=	codes/exec/

OBJ_DIR				=	build/
OBJ_M				=	$(addprefix $(OBJ_DIR), $(GENERAL_SRCS:.c=.o) $(MAIN_SRCS:.c=.o) $(TOKEN_PARSE_SRCS:.c=.o) $(BUILTIN_SRCS:.c=.o) $(REDIR_SRCS:.c=.o) $(EXEC_SRCS:.c=.o))

GENERAL				=	$(addprefix $(GENERAL_DIR), $(GENERAL_SRCS))
MAIN				=	$(addprefix $(MAIN_DIR), $(MAIN_SRCS))
TOKEN_PARSE			=	$(addprefix $(TOKEN_PARSE_DIR), $(TOKEN_PARSE_SRCS))
BUILTIN				=	$(addprefix $(BUILTIN_DIR), $(BUILTIN_SRCS))
REDIR				=	$(addprefix $(REDIR_DIR), $(REDIR_SRCS))
EXEC				=	$(addprefix $(EXEC_DIR), $(EXEC_SRCS))

LIBFT_DIR			=	includes/libft/
LIBFT				=	$(LIBFT_DIR)libft.a

LIBMS_DIR			=	includes/libms/
LIBMS				=	$(LIBMS_DIR)libms.a

LIBFT_OBJ			=	$(wildcard $(LIBFT_DIR)*.o)
LIBMS_OBJ			=	$(wildcard $(LIBMS_DIR)*.o)

LFLAGS				=	-lreadline
TERMCAP				=	-ltermcap

# Colors
RESET				=	\033[0m
RED					=	\033[1;31m
CYAN				=	\033[1;36m
PINK				=	\033[1;35m
GREEN				=	\033[1;32m
YELLOW				=	\033[1;33m
REWHITE				=	\033[1;7;97m
RECYAN				=	\033[1;7;36m
REPINK				=	\033[1;7;35m
RERED				=	\033[1;7;31m
REGREEN				=	\033[1;7;32m
REYELLOW			=	\033[1;7;33m

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
			@clear
			@mkdir -p $(OBJ_DIR)
			$(CC) $(FLAGS) -c $< -o $@
			@$(call update_progress)

$(OBJ_DIR)%.o: $(GENERAL_DIR)%.c $(HEADER)
			@clear
			@mkdir -p $(OBJ_DIR)
			$(CC) $(FLAGS) -c $< -o $@
			@$(call update_progress)

$(OBJ_DIR)%.o: $(TOKEN_PARSE_DIR)%.c $(HEADER)
			@mkdir -p $(OBJ_DIR)
			$(CC) $(FLAGS) -c $< -o $@
			@$(call update_progress)

$(OBJ_DIR)%.o: $(BUILTIN_DIR)%.c $(HEADER)
			@mkdir -p $(OBJ_DIR)
			$(CC) $(FLAGS) -c $< -o $@
			@$(call update_progress)

$(OBJ_DIR)%.o: $(REDIR_DIR)%.c $(HEADER)
			@mkdir -p $(OBJ_DIR)
			$(CC) $(FLAGS) -c $< -o $@
			@$(call update_progress)

$(OBJ_DIR)%.o: $(EXEC_DIR)%.c $(HEADER)
			@mkdir -p $(OBJ_DIR)
			$(CC) $(FLAGS) -c $< -o $@
			@$(call update_progress)

$(NAME): $(OBJ_M) $(LIBFT) $(LIBMS)
			$(CC) $(FLAGS) $(OBJ_M) $(LIBMS) $(LIBFT) $(LFLAGS) $(TERMCAP) -o $(NAME)
			@echo "\n$(GREEN)✅ Execution completed! ✅$(RESET)\n"
			@sleep 0.5
			@echo "$(CYAN)🎉 Minishell created 🎉\n"
			@sleep 1
			@echo "$(RECYAN)FYI:$(RESET) You can create a dependencies by calling $(YELLOW)make depend$(RESET)"
			@echo "if you want to see a leak report call $(YELLOW)make val$(RESET) to create $(YELLOW)leakreport.log$(RESET)"
			@echo "to check norminette, call $(YELLOW)make norm$(RESET) and see the report saved in $(YELLOW)norminette.log$(RESET)!\n\n"
			@sleep 1
			@echo "$(GREEN)Check github.com/vgomes-p/minishell-42/tree/main/project for a few tests for Minishell$(RESET)\n\n"
			@sleep 1
			@echo "$(YELLOW)Now you can run $(CYAN)./minishell$(RESET)\n\n"


$(LIBFT):
			@make -C $(LIBFT_DIR)

$(LIBMS): $(LIBFT)
			@make -C $(LIBMS_DIR)

val: $(NAME)
			-@rm leakreport.log
			@echo "\n$(REWHITE) RUN THIS COMMAND: $(RESET)"
			@echo "$(CYAN)valgrind --leak-check=full --show-leak-kinds=all --suppressions=ms.supp --log-file=leakreport.log ./minishell$(RESET)"

norm:
			@for file in $(LIBFT_DIR) $(LIBMS_DIR) $(GENERAL) $(MAIN) $(TOKEN_PARSE) $(BUILTIN) $(REDIR) $(EXEC) $(HEADER); do \
				if norminette $$file | grep -q "Error"; then \
					echo "$(RED)❌ $$file$(RESET)"; \
				else \
					echo "$(GREEN)✅ $$file$(RESET)"; \
				fi; \
			done
			-@norminette > norminette.log 2>&1
			@echo "$(CYAN)🆗 Norminette check complete! 🆗$(RESET)"
			@echo "$(CYAN)Norminette report saved in norminette.log!$(RESET)"

depend:
			@$(CC) -MM $(FLAGS) $(GENERAL) $(MAIN) $(TOKEN_PARSE) $(BUILTIN) $(REDIR) $(EXEC) | sed 's|^\(.*\)\.o:|$(OBJ_DIR)\1.o:|' > dependencies.mk
			@echo "\n$(REWHITE)Dependencies updated in dependencies.mk!$(RESET)\n"

all:		$(NAME)

clean:
			@$(RM) $(OBJ_M)
			@make clean -C $(LIBFT_DIR)
			@make clean -C $(LIBMS_DIR)


fclean: clean
			@clear
			@$(RM) $(NAME)
			@$(RM) dependencies.mk
			@$(RM) leakreport.log
			@$(RM) norminette.log
			@$(RM) build/
			@make fclean -C $(LIBFT_DIR)
			@make fclean -C $(LIBMS_DIR)
			@echo "$(RERED)Execution completed: minishell was completely deleted!$(RESET)\n"
			@sleep 1
			@echo "$(PINK)Cleaning terminal!$(RESET)"
			@sleep 1.5
			@clear
			@echo "$(GREEN)Você está na pasta:$(RESET)"
			@pwd

re:			fclean all


.PHONY:		all clean fclean re depend val norm