/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:07:47 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/06 17:10:20 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst_first;
	t_list	*new_lst;
	t_list	*new_node;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	content = f(lst->content);
	new_lst_first = ft_lstnew(content);
	if (!new_lst_first)
		return (del(content), NULL);
	new_lst = new_lst_first;
	lst = lst->next;
	while (lst)
	{
		content = f(lst->content);
		new_node = ft_lstnew(content);
		if (!new_node)
			return (del(content), ft_lstclear(&new_lst_first, del), NULL);
		new_lst->next = new_node;
		new_lst = new_node;
		lst = lst->next;
	}
	return (new_lst_first);
}

// void	*next_word(void *content)
// {
// 	char	*str;

// 	str = (char *)content;
// 	while (*str)
// 	{
// 		*str = *str + 1;
// 		str++;
// 	}
// 	return (str);
// }

// void	del(void *target)
// {
// 	free(target);
// }

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	t_list	*lst1;
// 	t_list	*lst2;
// 	t_list	*lst3;

// 	lst1 = malloc(sizeof(t_list) * 1);
// 	lst2 = malloc(sizeof(t_list) * 1);
// 	lst3 = malloc(sizeof(t_list) * 1);
// 	lst1->content = strdup("abc");
// 	lst1->next = lst2;
// 	lst2->content = strdup("def");
// 	lst2->next = lst3;
// 	lst3->content = strdup("ghi");
// 	lst3->next = NULL;
// 	ft_lstmap(lst1, next_word, del);
// 	printf("%s", (char *)lst1->content);
// }
