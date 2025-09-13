/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:33:44 by kaisogai          #+#    #+#             */
/*   Updated: 2025/08/05 19:31:08 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

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
