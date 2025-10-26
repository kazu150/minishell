/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 18:39:47 by cyang             #+#    #+#             */
/*   Updated: 2025/10/19 11:55:13 by cyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(char **args, t_env **env_list)
{
	t_env	*current;
	int		i;
	int		exist;
	char	*equal_pos;
	char	*key;
	char	*value;

	i = 1;
	current = *env_list;
	exist = 0;
	while (args[i])
	{
		equal_pos = ft_strchr(args[i], '=');
		if (!equal_pos)
		{
			i++;
			continue;
		}
		if (equal_pos == args[i])
		{
			ft_putendl_fd("bash: =: command not found", 2);
			return(127);
		}
		key = ft_substr(args[i], 0, equal_pos - args[i]);
		value = ft_strdup(equal_pos + 1);
		if (!key || !value)
		{
			free(key);
			free(value);
			return (1);
		}
		current = *env_list;
		exist = 0;
		while (current)
		{
			if (!(ft_strcmp(current->key, key)))
			{
				free(current->value);
				current->value = ft_strdup(value);
				exist = 1;
				break ;
			}
			current = current->next;
		}
		if (!exist)
			add_env_back(env_list, new_env(key, value));
		free(key);
		free(value);
		i++;
	}
	return (0);
}
