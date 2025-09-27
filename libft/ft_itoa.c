/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:27:26 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/07 21:21:10 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numlen(long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static long	get_unsigned_long(int n)
{
	long	ln;

	ln = n;
	if (ln < 0)
		return (-ln);
	else
		return (ln);
}

char	*ft_itoa(int n)
{
	long	ln;
	int		len;
	char	*result;
	int		is_minus;

	is_minus = 0;
	ln = get_unsigned_long(n);
	if (n < 0)
		is_minus = 1;
	len = numlen(ln);
	result = malloc(len + is_minus + 1);
	if (!result)
		return (NULL);
	result[len + is_minus] = 0;
	while (ln > 0)
	{
		result[len + is_minus - 1] = (ln % 10) + '0';
		ln = ln / 10;
		len--;
	}
	if (len == 1 && n == 0)
		result[0] = '0';
	if (is_minus)
		result[0] = '-';
	return (result);
}

// int	main(void)
// {
// 	printf("%s\n", ft_itoa(0));
// 	printf("%s\n", ft_itoa(1));
// 	printf("%s\n", ft_itoa(-1));
// 	printf("%s\n", ft_itoa(10));
// 	printf("%s\n", ft_itoa(-20));
// 	printf("%s\n", ft_itoa(125));
// 	printf("%s\n", ft_itoa(54300000));
// 	printf("%s\n", ft_itoa(2147483647));
// 	printf("%s\n", ft_itoa(-2147483647));
// 	printf("%s\n", ft_itoa(-2147483648));
// }