/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:27:20 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/06 17:11:12 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*bytes1;
	unsigned char	*bytes2;
	size_t			i;

	bytes1 = (unsigned char *)dest;
	bytes2 = (unsigned char *)src;
	i = 0;
	if (!src && !dest)
		return (dest);
	while (i < n)
	{
		if (dest < src)
			bytes1[i] = bytes2[i];
		else
			bytes1[n - i - 1] = bytes2[n - i - 1];
		i++;
	}
	return (dest);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char str1[20] = "1234567890";
// 	char str2[20] = "1234567890";
// 	char str3[20] = "1234567890";

// 	printf("Before:\n");
// 	printf("str1: %s\n", str1);
// 	printf("str2: %s\n", str2);
// 	printf("str3: %s\n", str3);

// 	memcpy(str1 + 2, str1, 8);
// 	ft_memmove(str2 + 2, str2, 8);
// 	ft_memmove(str3, str3 + 2, 8);

// 	printf("\nAfter:\n");
// 	printf("memcpy : %s\n", str1);
// 	printf("memmove1: %s\n", str2);
// 	printf("memmove2: %s\n", str3);
// }