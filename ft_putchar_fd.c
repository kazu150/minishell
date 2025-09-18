/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:21:26 by cyang             #+#    #+#             */
/*   Updated: 2025/09/18 10:48:08 by cyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}

// #include <fcntl.h>

// int	main(void)
// {
// 	int fd;
// 	char s[] = "Bonjour!";
// 	int	n = 0;

// 	fd = open("test_putchar_fd.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1)
// 		return (1);
// 	while (s[n])
// 	{
// 		ft_putchar_fd(s[n], fd);
// 		n++;
// 	}
// 	close(fd);
// 	return (0);
// }