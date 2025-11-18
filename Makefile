# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/03 16:26:12 by kaisogai          #+#    #+#              #
#    Updated: 2025/11/18 18:18:07 by cyang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
INCLUDE	= -I./ -I./libft -I/usr/local/opt/readline/include
READLINE = -L/usr/local/opt/readline/lib -lreadline
LIBFT	= libft/libft.a
SRCS	= main.c parse.c command.c tokenize.c tokenize_utils.c tokenize_utils2.c expand.c expand_utils.c builtin_fn/ft_echo.c heredoc.c builtin_fn/ft_pwd.c builtin_fn/ft_cd.c env.c builtin_fn/ft_env.c builtin_fn/ft_export.c builtin_fn/ft_exit.c builtin_fn/ft_unset.c builtin_fn/index.c utils/free.c utils/path.c utils/signal.c utils/error.c utils/string.c parse_utils.c parse_utils2.c parse_utils3.c builtin_fn/export_utils.c expand_with_var.c
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
