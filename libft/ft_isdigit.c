/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:27:32 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/06 17:26:54 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

// #include <stdio.h>
// #include <ctype.h>
// int main()
// {
//   printf("%d\n", ft_isdigit('a'));
//   printf("%d\n", ft_isdigit('B'));
//   printf("%d\n", ft_isdigit('0'));
//   printf("%d\n", ft_isdigit('&'));
//   printf("%d\n", isdigit('a'));
//   printf("%d\n", isdigit('B'));
//   printf("%d\n", isdigit('0'));
//   printf("%d\n", isdigit('&'));
// }