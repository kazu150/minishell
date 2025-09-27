/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:26:32 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/07 21:44:56 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char str[] = "abcdb";
// 	printf("%s", ft_strrchr(str, 'b'));
// 	printf("%s", strrchr(str, 'b'));
// 	char str1[] = "abc";
// 	printf("%s", ft_strrchr(str1, 'd'));
// 	printf("%s", strrchr(str1, 'd'));
// 	printf("%s", ft_strrchr(str1, 0));
// 	printf("%s", strrchr(str1, 0));
// }