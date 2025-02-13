# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgomes-p <vgomes-p@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 12:57:14 by vgomes-p          #+#    #+#              #
#    Updated: 2025/02/13 01:34:51 by vgomes-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	libft.a
CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror
AR			:=	ar -rcs
RM			:=	rm -rf

SRCS		:=	ft_isalpha.c ft_isdigit.c ft_strlen.c ft_isalnum.c ft_isascii.c \
				ft_isprint.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
				ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
				ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
				ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
				ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
				ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
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
				@echo "\n\n$(GREEN)✅ Success on creating libft! ✅$(DEFAULT)"

%.o: %.c
				$(CC) $(CFLAGS) -c $< -o $@

clean:
				$(RM) $(OBJS)


fclean: clean
			$(RM) $(NAME)
			@echo "$(RERED)libft was destroyed!$(DEFAULT)\n"

re: fclean all

.PHONY: all clean fclean re
