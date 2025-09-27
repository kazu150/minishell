/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nums.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 23:25:06 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/13 16:01:21 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_number(va_list ap)
{
	int	num;
	int	length;

	num = va_arg(ap, int);
	ft_putnbr_fd(num, 1);
	length = any_base_numlen(num, 10);
	return (length);
}

int	print_unsigned_number(va_list ap)
{
	unsigned int	num;
	int				length;

	num = va_arg(ap, unsigned int);
	ft_putuint_fd(num, 1);
	length = any_base_unsigned_numlen(num, 10);
	return (length);
}

int	print_any_based_number(va_list ap, char *base, int base_count)
{
	unsigned int	num;
	int				length;

	num = va_arg(ap, unsigned int);
	ft_putnbr_base(num, base);
	length = any_base_unsigned_numlen(num, base_count);
	return (length);
}

int	print_pointer(va_list ap, char *base)
{
	unsigned long	num;
	int				length;

	num = va_arg(ap, unsigned long);
	if (!num)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	ft_putstr_fd("0x", 1);
	length = 2;
	ft_putnbr_base(num, base);
	length += any_base_unsigned_numlen(num, 16);
	return (length);
}
