/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:27:35 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/06 17:26:52 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

// #include <stdio.h>
// #include <ctype.h>
// int main()
// {
//   printf("%d\n", ft_isascii('a'));
//   printf("%d\n", ft_isascii('B'));
//   printf("%d\n", ft_isascii('0'));
//   printf("%d\n", ft_isascii(-1));
//   printf("%d\n", ft_isascii(127));
//   printf("%d\n", ft_isascii(128));
//   printf("%d\n", isascii('a'));
//   printf("%d\n", isascii('B'));
//   printf("%d\n", isascii('0'));
//   printf("%d\n", isascii(-1));
//   printf("%d\n", isascii(127));
//   printf("%d\n", isascii(128));
// }