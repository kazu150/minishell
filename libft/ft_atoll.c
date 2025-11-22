/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:27:49 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/22 14:46:40 by kaisogai         ###   ########.fr       */
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

long long	ft_atoll(const char *nptr)
{
	int			i;
	int			is_minus;
	long long	result;

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
