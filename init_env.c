/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:50:57 by cyang             #+#    #+#             */
/*   Updated: 2025/10/12 11:00:42 by cyang            ###   ########.fr       */
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

t_env	*init_env(char **envp)
{
	t_env	*env_list;
	char	**env_split;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		env_split = ft_split(envp[i], '=');
		if (env_split && env_split[0])
			add_env_back(&env_list, new_env(env_split[0], env_split[1]));
		free_split(env_split);
		i++;
	}
	return (env_list);
}
