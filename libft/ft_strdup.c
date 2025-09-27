/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:50:27 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/06 17:11:59 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*str;

	i = 0;
	while (src[i] != 0)
	{
		i++;
	}
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (src[i] != 0)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("%s\n", ft_strdup(""));
// 	printf("%s\n", ft_strdup("a"));
// 	printf("%s\n", ft_strdup("aiueo"));
// 	printf("%s\n", ft_strdup("aiueoaiueoaiueoaiueoaiueoaiueo"));
// }