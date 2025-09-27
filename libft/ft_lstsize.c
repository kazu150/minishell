/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:07:39 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/06 17:10:28 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 1;
	if (lst == NULL)
		return (0);
	while (lst->next)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

// #include <stdio.h>

// int	main(void)
// {
// 	t_list *lst1;
// 	lst1 = malloc(sizeof(t_list) * 1);
// 	t_list *lst2;
// 	lst2 = malloc(sizeof(t_list) * 1);
// 	t_list *lst3;
// 	lst3 = malloc(sizeof(t_list) * 1);
// 	char str1[] = "abc";
// 	char str2[] = "def";
// 	char str3[] = "ghi";
// 	lst1->content = str1;
// 	lst1->next = lst2;
// 	lst2->content = lst2;
// 	lst2->next = lst3;
// 	lst3->content = str3;
// 	lst3->next = NULL;
// 	printf("%d\n", ft_lstsize(lst1));
// 	t_list *l = ((void *)0);
// 	printf("%d\n", ft_lstsize(l));
// }