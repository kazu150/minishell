/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:50:57 by cyang             #+#    #+#             */
/*   Updated: 2025/11/01 14:09:49 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = strdup(key);
	if (value)
		node->value = strdup(value);
	else
		node->value = strdup("");
	node->next = NULL;
	return (node);
}


void	add_env_back(t_env **env_list, t_env *new)
{
	t_env	*tmp;

	if (!env_list || !new)
		return ;
	if (!*env_list)
	{
		*env_list = new;
		return ;
	}
	tmp = *env_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_env	*init_env()
{
	t_env	*env_list;
	char	**env_split;
	int		i;

	env_list = NULL;
	i = 0;
	while (environ[i])
	{
		env_split = ft_split(environ[i], '=');
		if (env_split && env_split[0])
			add_env_back(&env_list, new_env(env_split[0], env_split[1]));
		free_split(env_split);
		i++;
	}
	return (env_list);
}
