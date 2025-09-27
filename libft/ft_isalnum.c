/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:27:41 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/06 17:26:45 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

// #include <ctype.h>
// #include <stdio.h>
// int main(){
//   printf("%d", ft_isalnum('b'));
//   printf("%d", ft_isalnum('A'));
//   printf("%d", ft_isalnum('1'));
//   printf("%d", ft_isalnum('-'));
//   printf("%d", isalnum('b'));
//   printf("%d", isalnum('A'));
//   printf("%d", isalnum('1'));
//   printf("%d", isalnum('-'));
// }