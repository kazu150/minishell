/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 21:07:16 by cyang             #+#    #+#             */
/*   Updated: 2025/11/21 16:38:22 by cyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **args, t_env *env_list)
{
	t_env	*current;

	current = env_list;
	if (args && args[1] != NULL)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (127);
	}
	while (current)
	{
		if (current->is_exported && current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}

int	update_existing_env(t_env *env_list, char *key, char *value)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (!(ft_strcmp(current->key, key)))
		{
			free(current->value);
			current->value = ft_strdup(value);
			return (1);
		}
		current = current->next;
	}
	return (0);
}
