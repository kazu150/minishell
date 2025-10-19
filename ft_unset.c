/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 15:13:01 by kaisogai          #+#    #+#             */
/*   Updated: 2025/10/19 16:04:29 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char *arg, t_env **env_list)
{
	t_env	*current;
	t_env	*prev;

	current = *env_list;
	prev = NULL;
	if (arg == NULL)
		return (0);
	while (current)
	{
		if (ft_strcmp(current->key, arg) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env_list = (*env_list)->next;
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}
