# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/03 16:26:12 by kaisogai          #+#    #+#              #
#    Updated: 2025/10/16 17:15:38 by kaisogai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
INCLUDE	= -I./ -I./libft -I/usr/local/opt/readline/include
READLINE = -L/usr/local/opt/readline/lib -lreadline
LIBFT	= libft/libft.a

SRCS	= main.c parse.c input.c output.c utils.c tokenize.c tokenize_utils.c tokenize_utils2.c expand.c expand_utils.c ft_echo.c heredoc.c ft_pwd.c ft_cd.c init_env.c ft_env.c ft_export.c ft_exit.c

OBJS	= $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -s -C libft

$(NAME): $(LIBFT) $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJS)
	make clean -s -C libft

fclean:	clean
	rm -f $(NAME)
		make fclean -s -C libft

re: fclean all

.PHONY: all clean fclean re
