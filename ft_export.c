/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 18:39:47 by cyang             #+#    #+#             */
/*   Updated: 2025/10/11 19:36:13 by cyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(char **args, t_env **env_list)
{
	t_env	*current;
	char	**env_split;
	int		i;
	int		exist;

	current = *env_list;
	i = 1;
	exist = 0;
	while (args[i])
	{
		env_split = ft_split(args[i], '=');
		if (env_split && env_split[0])
		{
			while (current)
			{
				if (!(ft_strcmp(current->key, env_split[0])))
				{
					free(current->value);
					current->value = ft_strdup(env_split[1]);
					exist = 1;
					break ;
				}
				current = current->next;
			}
			if (!exist)
			{
				add_env_back(env_list, new_env(env_split[0], env_split[1]));
			}
		}
		free_split(env_split);
		i++;
	}
}
