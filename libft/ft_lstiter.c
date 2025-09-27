/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:08:07 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/04 18:08:11 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

// void	count_up(void *num)
// {
// 	*(int *)num = *(int *)num + 1;
// }

// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	t_list lst1;
// 	t_list lst2;
// 	t_list lst3;
// 	int num1 = 100;
// 	int num2 = 200;
// 	int num3 = 300;
// 	lst1.content = &num1;
// 	lst1.next = &lst2;
// 	lst2.content = &num2;
// 	lst2.next = &lst3;
// 	lst3.content = &num3;
// 	lst3.next = NULL;
// 	ft_lstiter(&lst1, count_up);
// 	printf("%d\n", *(int *)lst1.content);
// 	printf("%d\n", *(int *)lst2.content);
// 	printf("%d\n", *(int *)lst3.content);
// }