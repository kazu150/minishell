/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:58:45 by cyang             #+#    #+#             */
/*   Updated: 2025/05/04 13:27:20 by cyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

// #include <fcntl.h>

// int	main(void)
// {
// 	char	s[] = "Salut!";
// 	int fd;

// 	fd = open("test_putendl_fd.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1)
// 		return (1);
// 	ft_putendl_fd(s, fd);
// 	close(fd);
// 	return (0);
// }
