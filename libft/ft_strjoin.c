/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:18:57 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/09 14:29:27 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *str1, const char *str2)
{
	char	*dest;
	int		str1_len;
	int		str2_len;
	int		i;

	str1_len = ft_strlen(str1);
	str2_len = ft_strlen(str2);
	dest = malloc((sizeof(char)) * (str1_len + str2_len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < str1_len)
	{
		dest[i] = str1[i];
		i++;
	}
	while (i - str1_len < str2_len)
	{
		dest[i] = str2[i - str1_len];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	str1[] = "aiueo";
// 	char	str2[] = "111";
// 	char	str3[] = "";
// 	char	str4[] = "111";
// 	char	str5[] = "aaa";
// 	char	str6[] = "";
// 	char	str7[] = "";
// 	char	str8[] = "";

// 	printf("%s\n", ft_strjoin(str1, str2));
// 	printf("%s\n", ft_strjoin(str3, str4));
// 	printf("%s\n", ft_strjoin(str5, str6));
// 	printf("%s\n", ft_strjoin(str7, str8));
// }
