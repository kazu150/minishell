/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:27:22 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/06 17:11:08 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*bytes1;
	unsigned char	*bytes2;
	size_t			i;

	if (!src && !dest)
		return (dest);
	bytes1 = (unsigned char *)dest;
	bytes2 = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		bytes1[i] = bytes2[i];
		i++;
	}
	return (dest);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char *str1 = 0;
// 	char *str2 = 0;
// 	memcpy(str1, str2, 0);
// 	printf("%s\n", str1);
// 	printf("%s\n", str2);

// 	char *ft_str1 = 0;
// 	char *ft_str2 = 0;
// 	ft_memcpy(ft_str1, ft_str2, 0);
// 	printf("%s\n", ft_str1);
// 	printf("%s\n", ft_str2);
// }