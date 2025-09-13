/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:26:37 by kaisogai          #+#    #+#             */
/*   Updated: 2025/08/26 13:49:34 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*u_s1;
	unsigned char	*u_s2;

	u_s1 = (unsigned char *)s1;
	u_s2 = (unsigned char *)s2;
	i = 0;
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (u_s1[i] - u_s2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return (u_s1[i] - u_s2[i]);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	printf("%d\n", strncmp("abc", "g", 3));
// 	printf("%d\n", ft_strncmp("abc", "g", 3));
// 	printf("%d\n", strncmp("abc", "", 3));
// 	printf("%d\n", ft_strncmp("abc", "", 3));
// 	printf("%d\n", strncmp("abc", "abb", 2));
// 	printf("%d\n", ft_strncmp("abc", "abb", 2));
// 	printf("%d\n", strncmp("abc", "abb", 0));
// 	printf("%d\n", ft_strncmp("abc", "abb", 0));
// 	printf("%d\n", strncmp("", "", 0));
// 	printf("%d\n", ft_strncmp("", "", 0));
// 	char *s1 = "\200";
// 	char *s2 = "\0";
// 	printf("s1 is %s\n", (char *)s1);
// 	printf("%d\n", strncmp(s1, s2, 1));
// 	printf("%d\n", ft_strncmp(s1, s2, 1));
// 	char *s1_2 = "\x12\xff\x65\x12\xbd\xde\xad";
// 	char *s2_2 = "\x12\x02";
// 	printf("%d\n", strncmp(s1_2, s2_2, 6));
// 	printf("%d\n", ft_strncmp(s1_2, s2_2, 6));
// }
