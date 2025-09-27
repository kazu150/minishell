/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:26:56 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/06 17:27:30 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

// void	func(unsigned int i, char *s)
// {
// 	int	j;

// 	j = 0;
// 	if (i % 2)
// 	{
// 		while (s[j])
// 		{
// 			s[j]++;
// 			j++;
// 		}
// 	}
// }

// #include <stdio.h>

// int	main(void)
// {
// 	char s[] = "aaaaaaaaaaa";
// 	ft_striteri(s, func);
// 	printf("%s", s);
// }