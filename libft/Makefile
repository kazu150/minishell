# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/03 16:26:12 by kaisogai          #+#    #+#              #
#    Updated: 2025/05/07 22:20:50 by kaisogai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a
CC			= cc
CFLAGS 		= -Wall -Wextra -Werror
BONUS		= bonus
SRCS = \
	ft_isalnum.c ft_isprint.c ft_memcpy.c ft_putendl_fd.c \
	ft_strchr.c ft_strlcat.c ft_strncmp.c ft_substr.c \
	ft_atoi.c ft_isalpha.c ft_itoa.c ft_memmove.c ft_putnbr_fd.c \
	ft_strdup.c ft_strlcpy.c ft_strnstr.c ft_tolower.c \
	ft_bzero.c ft_isascii.c ft_memchr.c ft_memset.c ft_putstr_fd.c \
	ft_striteri.c ft_strlen.c ft_strrchr.c ft_toupper.c \
	ft_calloc.c ft_isdigit.c ft_memcmp.c ft_putchar_fd.c ft_split.c \
	ft_strjoin.c ft_strmapi.c ft_strtrim.c \
	ft_printf.c utils/ft_putnbr_base.c utils/ft_putuint_fd.c utils/numlen.c utils/print_nums.c utils/print_words.c
BONUS_SRCS = \
	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS = $(patsubst %.c, %.o, $(SRCS))
BONUS_OBJS = $(patsubst %.c, %.o, $(BONUS_SRCS))

all: $(NAME)

bonus: $(NAME)

ifeq ($(filter $(BONUS),$(MAKECMDGOALS)),$(BONUS))
ALL_OBJS = $(OBJS) $(BONUS_OBJS)
else
ALL_OBJS = $(OBJS)
endif

$(NAME): $(ALL_OBJS)
	ar rcs $(NAME) $(ALL_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -I . -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus