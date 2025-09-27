/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:27:47 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/06 17:09:01 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*d;
	size_t			i;

	d = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		d[i] = 0;
		i++;
	}
}

// #include <stdio.h>
// #include <strings.h>

// int	main(void)
// {
// 	char str[] = "aiueo";
// 	bzero(str, 3);
// 	for (int i = 0; i < 5; i++)
// 		printf("%c ", str[i]);

// 	char ft_str[] = "aiueo";
// 	ft_bzero(ft_str, 3);
// 	for (int i = 0; i < 5; i++)
// 		printf("%c ", ft_str[i]);
// }