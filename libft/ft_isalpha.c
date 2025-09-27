/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:27:38 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/06 17:26:49 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

// #include <stdio.h>
// #include <ctype.h>
// int main()
// {
//   printf("%d\n", ft_isalpha('a'));
//   printf("%d\n", ft_isalpha('B'));
//   printf("%d\n", ft_isalpha('0'));
//   printf("%d\n", isalpha('a'));
//   printf("%d\n", isalpha('B'));
//   printf("%d\n", isalpha('0'));
// }