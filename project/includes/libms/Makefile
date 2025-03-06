# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgomes-p <vgomes-p@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 12:57:14 by vgomes-p          #+#    #+#              #
#    Updated: 2025/03/06 13:45:44 by vgomes-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	libms.a
CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror
AR			:=	ar -rcs
RM			:=	rm -rf

SRCS		:=	lms_putchar.c lms_putstr.c lms_strcmp.c lms_realloc.c \
				lms_strncpy.c lms_strndup.c lms_strstr.c lms_joinstr_free.c \
				lms_isnum.c lms_strjoin_char.c
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
				@echo "\n$(GREEN)✅ Success on creating libms! ✅$(DEFAULT)"

%.o: %.c
				$(CC) $(CFLAGS) -c $< -o $@

clean:
				$(RM) $(OBJS)

fclean: clean
				$(RM) $(NAME)
				@echo "$(RERED)libms was destroyed!$(DEFAULT)\n"

re: fclean all

.PHONY: all clean fclean re
