# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/03 16:26:12 by kaisogai          #+#    #+#              #
#    Updated: 2025/09/13 13:17:47 by kaisogai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
SRCS		= main.c input.c output.c utils.c ft_split.c ft_strjoin.c ft_strncmp.c split_utils.c
OBJS		= main.o input.o output.o utils.o ft_split.o ft_strjoin.o ft_strncmp.o split_utils.o

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
