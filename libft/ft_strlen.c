/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:26:41 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/06 17:12:16 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
//   printf("%d\n", strlen(""));
//   printf("%d\n", strlen("aiueo"));
//   printf("%d\n", strlen("          "));
//   printf("%d\n", ft_strlen(""));
//   printf("%d\n", ft_strlen("aiueo"));
//   printf("%d\n", ft_strlen("          "));
// }