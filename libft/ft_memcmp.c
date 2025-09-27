/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:27:23 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/06 17:11:04 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*bytes1;
	unsigned char	*bytes2;

	i = 0;
	bytes1 = (unsigned char *)s1;
	bytes2 = (unsigned char *)s2;
	while (i < n)
	{
		if (bytes1[i] != bytes2[i])
			return (bytes1[i] - bytes2[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	*s1;
// 	char	*s2;
// 	char	*s1_2;
// 	char	*s2_2;

// 	printf("%d\n", memcmp("abc", "g", 3));
// 	printf("%d\n", ft_memcmp("abc", "g", 3));
// 	printf("%d\n", memcmp("abc", "abb", 3));
// 	printf("%d\n", ft_memcmp("abc", "abb", 3));
// 	printf("%d\n", memcmp("", "", 0));
// 	printf("%d\n", ft_memcmp("", "", 0));
// 	printf("%d\n", memcmp("", "", 1));
// 	printf("%d\n", ft_memcmp("", "", 1));
// 	printf("%d\n", memcmp("abc", "g", 3));
// 	printf("%d\n", ft_memcmp("abc", "g", 3));
// 	s1 = "\xff\xaa\xde\x12";
// 	s2 = "\xff\xaa\xde\x12MACOSAAAAA";
// 	printf("%d\n", memcmp(s1, s2, 4));
// 	printf("%d\n", ft_memcmp(s1, s2, 4));
// 	s1_2 = "\xff\xaa\xde\xffMACOSX\xff";
// 	s2_2 = "\xff\xaa\xde\x02";
// 	printf("%d\n", memcmp(s1_2, s2_2, 8));
// 	printf("%d\n", ft_memcmp(s1_2, s2_2, 8));
// }
