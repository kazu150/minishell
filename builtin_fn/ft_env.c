/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 21:07:16 by cyang             #+#    #+#             */
/*   Updated: 2025/11/22 15:44:26 by kaisogai         ###   ########.fr       */
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

void update_env_list(t_env **env_list, char *key, char *value)
{
	t_env	*target;

	if (update_existing_env(*env_list, key, value))
	{
		target = *env_list;
		while (target)
		{
			if (ft_strcmp(target->key, key) == 0)
			{
				target->is_exported = 1;
				break ;
			}
			target = target->next;
		}
	}
	else
		add_env_back(env_list, new_env(key, value, 1));
}
