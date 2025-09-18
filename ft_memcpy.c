/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:56:04 by cyang             #+#    #+#             */
/*   Updated: 2025/09/18 10:48:11 by cyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (dest == NULL && src == NULL)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	i = 0;
	if (d == s || n == 0)
		return (dest);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char a[10] = "12345";
// 	char b[10] = "12345";

// 	ft_memcpy(a, "abc", 3);
// 	memcpy(b, "abc", 3);

// 	printf("%s\n", a);
// 	printf("%s\n", b);

// 	return (0);
// }