/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 15:13:01 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/16 15:10:27 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	remove_key_value(char *arg, t_env *current, t_env *prev,
		t_env **env_list)
{
	if (ft_strcmp(current->key, arg) == 0)
	{
		if (prev)
			prev->next = current->next;
		else
			*env_list = (*env_list)->next;
		free_key_value(current->key, current->value);
		free(current);
		return (1);
	}
	return (0);
}

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
			if (remove_key_value(arg[i], current, prev, env_list) == 1)
				break ;
			prev = current;
			current = current->next;
		}
		i++;
	}
	return (0);
}
