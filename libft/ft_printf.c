/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:14:29 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/15 12:07:32 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// invalid conv specifiers returns -1
static int	manage_conv_specifiers(const char *input, va_list ap)
{
	if (*(input + 1) == 's')
		return (print_string(ap));
	if (*(input + 1) == 'c')
		return (print_char(ap));
	if (*(input + 1) == 'd' || *(input + 1) == 'i')
		return (print_number(ap));
	if (*(input + 1) == 'u')
		return (print_unsigned_number(ap));
	if (*(input + 1) == 'x')
		return (print_any_based_number(ap, "0123456789abcdef", 16));
	if (*(input + 1) == 'X')
		return (print_any_based_number(ap, "0123456789ABCDEF", 16));
	if (*(input + 1) == 'p')
		return (print_pointer(ap, "0123456789abcdef"));
	if (*(input + 1) == '%')
		return (ft_putchar_fd('%', 1), 1);
	return (-1);
}

// if receives invalid arg letter, return -1
static int	print_result(const char *input, va_list ap)
{
	int	i;
	int	letters_count;
	int	arg_letters_count;

	i = 0;
	letters_count = 0;
	while (input[i])
	{
		if (input[i] == '%')
		{
			arg_letters_count = manage_conv_specifiers(&input[i], ap);
			letters_count += arg_letters_count;
			if (arg_letters_count != -1)
				i += 2;
			else
				return (-1);
		}
		else
		{
			ft_putchar_fd(input[i++], 1);
			letters_count++;
		}
	}
	return (letters_count);
}

// test command: cc -I./include test.c libftprintf.a libft/libft.a -o test
int	ft_printf(const char *input, ...)
{
	va_list	ap;
	int		letters_count;

	if (!input)
		return (-1);
	va_start(ap, input);
	letters_count = print_result(input, ap);
	va_end(ap);
	return (letters_count);
}
