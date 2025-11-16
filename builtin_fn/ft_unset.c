/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 15:13:01 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/16 03:26:22 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **arg, t_env **env_list)
{
	t_env	*current;
	t_env	*prev;
	int		i;


	if (!arg || !arg[1])
		return (0);
	i = 0;
	while (arg[i])
	{
		current = *env_list;
		prev = NULL;
		while (current)
		{
			if (ft_strcmp(current->key, arg[i]) == 0)
			{
				if (prev)
					prev->next = current->next;
				else
					*env_list = (*env_list)->next;
				free_key_value(current->key, current->value);
				free(current);
				break;
			}
			prev = current;
			current = current->next;
		}
		i++;
	}
	return (0);
}
