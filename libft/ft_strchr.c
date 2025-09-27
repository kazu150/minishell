/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:27:03 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/07 21:44:36 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((unsigned char)s[i] == (unsigned char)c)
		return ((char *)&s[i]);
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char str[] = "abc";
// 	printf("%s\n", ft_strchr(str, 'b'));
// 	printf("%s\n", strchr(str, 'b'));
// 	char str1[] = "abc";
// 	printf("%s\n", ft_strchr(str1, 'd'));
// 	printf("%s\n", strchr(str1, 'd'));
// 	// char *str2 = 0;
// 	// printf("%s\n", ft_strchr(str2, 'd'));
// 	// printf("%s\n", strchr(str2, 'd'));
// 	// char str3[] = "abcde";
// 	// printf("%s\n", ft_strchr(str3, '\0'));
// 	// printf("%s\n", strchr(str3, '\0'));
// }