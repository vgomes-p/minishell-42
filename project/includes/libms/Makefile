# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 12:57:14 by vgomes-p          #+#    #+#              #
#    Updated: 2025/01/21 14:37:36 by vgomes-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	libms.a
CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror
AR			:=	ar -rcs
RM			:=	rm -rf

SRCS		:=	lms_putchar.c lms_putstr.c lms_strcmp.c lms_putenv.c lms_setenv.c \
				lms_unsetenv.c lms_realloc.c lms_strncpy.c lms_strndup.c
OBJS		:=	$(SRCS:.c=.o)

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

all: $(NAME)

$(NAME): $(OBJS)
				$(AR) $(NAME) $(OBJS)
				@echo -e "$(REGREEN)Execution completed: $(NAME) created!$(DEFAULT)"

%.o: %.c
				$(CC) $(CFLAGS) -c $< -o $@

clean:
				$(RM) $(OBJS)
				@echo -e "$(REYELLOW)Execution completed: libms was deleted!$(DEFAULT)"

fclean: clean
			$(RM) $(NAME)
			@echo -e "$(RERED)Execution completed: libms was completely deleted!$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean re
