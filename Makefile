# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/03 16:26:12 by kaisogai          #+#    #+#              #
#    Updated: 2025/09/23 11:23:04 by kaisogai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
SRCS		= main.c parse.c input.c output.c utils.c ft_split.c ft_strjoin.c ft_strncmp.c split_utils.c split_utils2.c
OBJS		= main.o parse.o input.o output.o utils.o ft_split.o ft_strjoin.o ft_strncmp.o split_utils.o split_utils2.o

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
