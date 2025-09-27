/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:26:27 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/07 21:39:32 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	int		len;
	int		i;
	int		k;
	char	*dest;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (len > i && ft_strchr(set, s1[len - 1]))
		len--;
	dest = malloc(len - i + 1);
	if (!dest)
		return (NULL);
	k = 0;
	while (i < len)
		dest[k++] = s1[i++];
	dest[k] = '\0';
	return (dest);
}

// int	main(void)
// {
// 	char s1[] = "ueueueeeeauuaaau";
// 	char set[] = "ue";
// 	printf("%s", ft_strtrim(s1, set));
// }
