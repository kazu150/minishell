/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:27:25 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/06 17:10:45 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*bytes;

	i = 0;
	bytes = (unsigned char *)s;
	while (i < n)
	{
		if (bytes[i] == (unsigned char)c)
			return (&bytes[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	str[] = "abc";
// 	char	str1[] = "abc";
// 	char	str2[] = "a\0c";
// 	int		tab[7] = {-49, 49, 1, -1, 0, -2, 2};

// 	printf("%s\n", (char *)ft_memchr(str, 'b', 3));
// 	printf("%s\n", (char *)memchr(str, 'b', 3));
// 	printf("%s\n", (char *)ft_memchr(str1, 'd', 3));
// 	printf("%s\n", (char *)memchr(str1, 'd', 3));
// 	printf("%s\n", (char *)ft_memchr(str2, 0, 3));
// 	printf("%s\n", (char *)memchr(str2, 0, 3));
// 	printf("minus test: %s\n", (char *)ft_memchr(tab, -1, 7));
// 	printf("minus test: %s\n", (char *)memchr(tab, -1, 7));
// }
