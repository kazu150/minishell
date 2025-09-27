/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:27:17 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/06 17:11:15 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*bytes;
	size_t			i;

	bytes = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		bytes[i] = c;
		i++;
	}
	return (b);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	// check on normal string
// 	char buf1[16];
// 	memset(buf1, 'a', 16);
// 	buf1[15] = 0;

// 	for (size_t i = 0; i < sizeof(buf1); i++)
// 	{
// 		printf("%02x ", buf1[i]);
// 		if ((i + 1) % 16 == 0)
// 			printf("\n");
// 	}

// 	printf("\n\n");
// 	// array(int)
// 	int arr[5];
// 	memset(arr, 'a', 5);
// 	unsigned char *bytes1 = (unsigned char *)arr;

// 	for (size_t i = 0; i < sizeof(arr); i++)
// 	{
// 		printf("%02x ", bytes1[i]);
// 		if ((i + 1) % 16 == 0)
// 			printf("\n");
// 	}

// 	printf("\n\n");
// 	// struct
// 	typedef struct
// 	{
// 		int				id;
// 		char			name[20];
// 	} Person;

// 	Person				people[3];
// 	memset(people, 'a', 5);

// 	unsigned char		*bytes = (unsigned char *)people;

// 	for (size_t i = 0; i < sizeof(people); i++)
// 	{
// 		printf("%02x ", bytes[i]);
// 		if ((i + 1) % 16 == 0)
// 			printf("\n");
// 	}

// 	printf("\n\n");

// 	char				ft_buf1[16];
// 	ft_memset(ft_buf1, 'a', 16);
// 	ft_buf1[15] = 0;

// 	for (size_t i = 0; i < sizeof(ft_buf1); i++)
// 	{
// 		printf("%02x ", ft_buf1[i]);
// 		if ((i + 1) % 16 == 0)
// 			printf("\n");
// 	}

// 	printf("\n\n");
// 	int					ft_arr[5];
// 	ft_memset(ft_arr, 'a', 5);
// 	unsigned char		*ft_bytes1 = (unsigned char *)ft_arr;

// 	for (size_t i = 0; i < sizeof(ft_arr); i++)
// 	{
// 		printf("%02x ", ft_bytes1[i]);
// 		if ((i + 1) % 16 == 0)
// 			printf("\n");
// 	}

// 	printf("\n\n");
// 	typedef struct
// 	{
// 		int				id;
// 		char			name[20];
// 	} FtPerson;

// 	FtPerson			ft_people[3];
// 	ft_memset(ft_people, 'a', 5);
// 	unsigned char		*ft_bytes = (unsigned char *)ft_people;

// 	for (size_t i = 0; i < sizeof(ft_people); i++)
// 	{
// 		printf("%02x ", ft_bytes[i]);
// 		if ((i + 1) % 16 == 0)
// 			printf("\n");
// 	}
// }