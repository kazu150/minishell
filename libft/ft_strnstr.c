/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:26:04 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/01 15:34:54 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == 0)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			while (haystack[i + j] && needle[j] && haystack[i + j] == needle[j])
			{
				j++;
				if (i + j <= len && !needle[j])
					return ((char *)&haystack[i]);
			}
		}
		i++;
	}
	return (0);
}

// #include <bsd/string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char haystack[] = "aiueokaaaaakikukaaeko";
// 	char needle[] = "kaaaa";
// 	char needle1[] = "";
// 	printf("%s\n", strnstr(haystack, needle, 11));
// 	printf("%s\n", ft_strnstr(haystack, needle, 11));
// 	printf("%s\n", strnstr(haystack, needle1, 11));
// 	printf("%s\n", ft_strnstr(haystack, needle1, 11));
// 	char *big = "123456789";
// 	char *little = "9";
// 	size_t max = 8;
// 	const char *s1 = strnstr(big, little, max);
// 	const char *s2 = ft_strnstr(big, little, max);
// 	printf("%s\n", s1);
// 	printf("%s\n", s2);
// 	char *s1_1 = "AAAAAAAAAAAAA";
// 	size_t m = strlen(s1_1);
// 	const char *i1 = strnstr(s1_1, s1_1, m);
// 	const char *i2 = ft_strnstr(s1_1, s1_1, m);
// 	printf("%s\n", i1);
// 	printf("%s\n", i2);
// }