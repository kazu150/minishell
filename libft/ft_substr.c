/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:26:00 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/07 21:38:39 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	s_len;

	i = 0;
	s_len = 0;
	if (!s)
		return (NULL);
	while (s[s_len])
		s_len++;
	if (start >= s_len)
		str = malloc(1);
	else if (start + len > s_len)
		str = malloc(s_len - start + 1);
	else
		str = malloc(len + 1);
	if (!str)
		return (NULL);
	while (i < len && start + i < s_len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char str1[] = "";
// 	printf("%s\n", ft_substr(str1, 0, 0));
// 	char str2[] = "aiueo";
// 	printf("%s\n", ft_substr(str2, 2, 3));

// 	char *str = "i just want this part #############";
// 	size_t size = 10;
// 	int ret_size;

// 	printf("%s\n", ft_substr(str, 5, size));
// 	printf("%s\n", ft_substr(str, 0, 10));
// }
