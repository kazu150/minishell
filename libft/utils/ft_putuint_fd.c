/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuint_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:08:40 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/15 13:28:01 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putuint_fd(unsigned int n, int fd)
{
	char	c;

	// if (n < 0)
	// {
	// 	write(fd, "-", 1);
	// 	n = n * -1;
	// }
	c = '0' + (n % 10);
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	write(fd, &c, 1);
}
