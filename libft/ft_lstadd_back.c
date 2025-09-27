/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:09:11 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/06 17:09:38 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next)
	{
		current = current->next;
	}
	current->next = new;
}

// #include <stdio.h>

// t_list	*ft_lstlast(t_list *lst)
// {
// 	while (lst->next)
// 	{
// 		lst = lst->next;
// 	}
// 	return (lst);
// }
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
// 	lst1->next = lst2;
// 	lst2->content = lst2;
// 	lst2->next = NULL;
// 	new->content = str3;
// 	new->next = NULL;

// 	ft_lstadd_back(&lst1, new);
// 	printf("%s", (char *)ft_lstlast(lst1)->content);
// }