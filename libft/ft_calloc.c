/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:25:51 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/08 17:46:29 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_size_max(void)
{
	return ((size_t)-1);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*bytes;

	if (nmemb == 0 || size == 0)
	{
		bytes = malloc(0);
		if (!bytes)
			return (NULL);
		return (bytes);
	}
	if (nmemb > get_size_max() / size)
		return (NULL);
	bytes = malloc(nmemb * size);
	if (!bytes)
		return (NULL);
	ft_bzero(bytes, nmemb * size);
	return (bytes);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	str[] = "aiueo";
// 	char	*str1;

// 	str1 = ft_calloc(sizeof(char), 6);
// 	for (int i = 0; i < 6; i++)
// 		str1[i] = str[i];
// 	printf("%s", str1);
// }
