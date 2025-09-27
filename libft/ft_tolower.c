/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:26:21 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/06 17:27:47 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c -= 'A' - 'a';
	return (c);
}

// #include <stdio.h>
// int main()
// {
//   printf("%c", ft_tolower('a'));
//   printf("%c", ft_tolower('A'));
//   printf("%c", ft_tolower('.'));
// }