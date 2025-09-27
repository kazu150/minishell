/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:26:18 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/06 17:27:50 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c += 'A' - 'a';
	return (c);
}

// #include <stdio.h>
// int main()
// {
//   printf("%c", ft_toupper('a'));
//   printf("%c", ft_toupper('A'));
//   printf("%c", ft_toupper('.'));
// }