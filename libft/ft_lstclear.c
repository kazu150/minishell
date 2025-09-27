/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:08:09 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/06 17:09:46 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*del_target;

	if (!del)
		return ;
	while (*lst)
	{
		del_target = *lst;
		*lst = (*lst)->next;
		del(del_target->content);
		free(del_target);
	}
	*lst = NULL;
}

// void	del(void *target)
// {
// 	free(target);
// }

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	t_list *lst1;
// 	lst1 = malloc(sizeof(t_list) * 1);
// 	t_list *lst2;
// 	lst2 = malloc(sizeof(t_list) * 1);
// 	t_list *lst3;
// 	lst3 = malloc(sizeof(t_list) * 1);
// 	lst1->content = strdup("abc");
// 	lst1->next = lst2;
// 	lst2->content = strdup("def");
// 	lst2->next = lst3;
// 	lst3->content = strdup("ghi");
// 	lst3->next = NULL;
// 	ft_lstclear(&lst1, del);
// 	// printf("%s\n", (char *)lst1);
// 	// printf("%s\n", (char *)lst2);
// 	// printf("%s\n", (char *)lst3);
// }