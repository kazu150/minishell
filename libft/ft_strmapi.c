/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:25:35 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/07 21:53:19 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	int				size;
	char			*result;
	unsigned int	i;

	size = 0;
	i = 0;
	while (s[size])
		size++;
	result = malloc(size + 1);
	if (!result)
		return (NULL);
	while (s[i])
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = 0;
	return (result);
}

// char	func(unsigned int i, char c)
// {
// 	if (i % 2)
// 		c += 'A' - 'a';
// 	return (c);
// }

// #include <stdio.h>

// int	main(void)
// {
// 	char s[] = "abcdefghij";

// 	printf("%s", ft_strmapi(s, func));
// }