/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:27:49 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/07 21:22:06 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	if (c == ' ' || c == '\f' || c == '\r' || c == '\n' || c == '\t'
		|| c == '\v')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	is_minus;
	int	result;

	is_minus = 0;
	i = 0;
	result = 0;
	while (is_space(nptr[i]))
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		is_minus = 1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (is_minus)
			result = (result * 10 - (nptr[i] - '0'));
		else
			result = (result * 10 + (nptr[i] - '0'));
		i++;
	}
	return (result);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("%d\n", ft_atoi("42"));
// 	printf("%d\n", ft_atoi(" "));
// 	printf("%d\n", ft_atoi("   			-1"));
// 	printf("%d\n", ft_atoi("abc123"));
// 	printf("%d\n", ft_atoi("42abc"));
// 	printf("%d\n", ft_atoi("-4200abc"));
// 	printf("%d\n", ft_atoi("+ 42"));
// 	printf("%d\n", ft_atoi("-00000001"));
// 	printf("%d\n", ft_atoi("-1"));
// 	printf("%d\n", ft_atoi("\t\v\f\r\n \f-6050"));
// }