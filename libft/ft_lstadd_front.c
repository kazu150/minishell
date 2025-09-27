/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:09:21 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/06 17:09:54 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	new->next = *lst;
	*lst = new;
}

// #include <stdio.h>

// int	main(void)
// {
// 	t_list *lst1;
// 	lst1 = malloc(sizeof(t_list) * 1);
// 	t_list *lst2;
// 	lst2 = malloc(sizeof(t_list) * 1);
// 	t_list *new;
// 	new = malloc(sizeof(t_list) * 1);
// 	char str1[] = "abc";
// 	char str2[] = "def";
// 	char str3[] = "123";
// 	lst1->content = str1;
// 	lst1->next = NULL;
// 	lst1->next = lst2;
// 	lst2->content = lst2;
// 	lst2->next = NULL;
// 	new->content = str3;
// 	new->next = NULL;

// 	printf("%s", (char *)lst1->content);
// 	ft_lstadd_front(&lst1, new);
// 	printf("%s", (char *)lst1->content);
// }