/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:26:48 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/06 17:12:10 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	s_size;
	size_t	d_size;

	i = 0;
	s_size = 0;
	d_size = 0;
	while (src[s_size])
		s_size++;
	while (d_size < dstsize && dst[d_size])
		d_size++;
	while (src[i] && d_size + i + 1 < dstsize)
	{
		dst[i + d_size] = src[i];
		i++;
	}
	if (d_size + i < dstsize)
		dst[d_size + i] = 0;
	return (d_size + s_size);
}

// #include <bsd/string.h>
// #include <stdio.h>
// #include <string.h>

// check null pattern
// int main()
// {
// 	strlcat(NULL, "abc", 0);
// 	ft_strlcat(NULL, "abc", 0);
// }

// bsd
// int	main(void)
// {
// 	char	*str;
// 	char	buff1[0xF00] = "there is no stars in the sky";
// 	char	buff2[0xF00] = "there is no stars in the sky";
// 	size_t	max;
// 	size_t	r2;

// 	str = "the cake is a lie !\0I'm hidden lol\r\n";
// 	max = strlen("the cake is a lie !\0I'm hidden lol\r\n") + 4;
// 	r2 = strlcat(buff2, str, 5);
// 	printf("%s\n", buff2);
// 	printf("%zu", r2);
// }

// ft
// int	main(void)
// {
// 	char *str;
// 	char buff1[0xF00] = "there is no stars in the sky";
// 	char buff2[0xF00] = "there is no stars in the sky";
// 	size_t max;
// 	size_t r2;

// 	str = "the cake is a lie !\0I'm hidden lol\r\n";
// 	max = strlen("the cake is a lie !\0I'm hidden lol\r\n") + 4;
// 	r2 = ft_strlcat(buff2, str, 5);
// 	printf("%s\n", buff2);
// 	printf("%zu", r2);
// }