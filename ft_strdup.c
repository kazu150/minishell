/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:14:05 by cyang             #+#    #+#             */
/*   Updated: 2025/09/18 10:53:17 by cyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s)
{
	char	*t;
	size_t	total_len;

	total_len = ft_strlen(s) + 1;
	t = malloc (total_len * sizeof(char));
	if (t == NULL)
		return (NULL);
	ft_strlcpy(t, s, total_len);
	return (t);
}

// #include <stdio.h>
// int	main(void)
// {
// 	const char *original = "Salut";
// 	char *copy = ft_strdup(original);
// 	printf("%s\n", copy);
// 	return (0);

// }