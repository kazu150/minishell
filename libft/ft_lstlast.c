/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:08:01 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/06 17:10:15 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
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
// 	printf("%s", (char *)ft_lstlast(lst1)->content);
// }