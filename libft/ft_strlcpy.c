/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:26:46 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/06 17:12:13 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = 0;
	while (src[src_len] != 0)
		src_len++;
	if (size == 0)
		return (src_len);
	while (i < size - 1 && i < src_len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (src_len);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	// printf("%d\n", strlcpy(""));
// 	// printf("%d\n", strlcpy("aiueo"));
// 	// printf("%d\n", strlcpy("          "));
// 	// printf("%d\n", ft_strlcpy(");
// 	char str[] = "aiueo";
// 	printf("%d\n", ft_strlcpy(str, "abc", 3));
// 	printf("%s\n", str);
// }