/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:41:29 by cyang             #+#    #+#             */
/*   Updated: 2025/09/18 10:53:38 by cyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	srclen;

	if (src == NULL)
		return (0);
	srclen = ft_strlen(src);
	if (dest == NULL || size == 0)
		return (srclen);
	i = 0;
	while (i < (size - 1) && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (srclen);
}

// #include <stdio.h>

// int main(void)
// {
//     char dest[10];
//     const char *src = "Bonjour";

//     size_t result = ft_strlcpy(dest, src, sizeof(dest));

//     printf("%zu\n", result);
// 	printf("%s\n", dest);
//     return 0;
// }