/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:07:51 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/06 17:10:09 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!del)
		return ;
	del(lst->content);
	free(lst);
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
// 	ft_lstdelone(lst2, del);
// 	printf("%s\n", (char *)lst1->content);
// 	printf("%s\n", (char *)lst3->content);
// 	free(lst1->content);
// 	free(lst1);
// 	free(lst3->content);
// 	free(lst3);
// }