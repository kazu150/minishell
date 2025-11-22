/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 17:19:43 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/22 17:23:43 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_list(t_env *list_current)
{
	int	count;

	count = 0;
	while (list_current)
	{
		if (list_current->is_exported)
			count++;
		list_current = list_current->next;
	}
	return (count);
}
