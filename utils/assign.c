/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:27:46 by cyang             #+#    #+#             */
/*   Updated: 2025/11/23 00:02:39 by cyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_assignment_only(t_list *assigns, t_data *data)
{
	char	*equal;
	char	*key;
	char	*value;
	t_list	*tmp;

	tmp = assigns;
	while (tmp)
	{
		equal = ft_strchr((char *)tmp->content, '=');
		if (equal)
		{
			key = ft_substr((char *)tmp->content, 0,
					equal - (char *)tmp->content);
			value = ft_strdup(equal + 1);
			if (!update_existing_env(data->env_list, key, value))
				add_env_back(&data->env_list, new_env(key, value, 0));
			free_key_value(key, value);
		}
		tmp = tmp->next;
	}
}

static char	**create_new_envp_array(char **base_envp, int count,
	t_list *assigns, int i)
{
	char	**new_envp;
	int		j;
	t_list	*tmp;

	new_envp = malloc(sizeof(char *) * (count + i + 1));
	if (!new_envp)
		error_exit(MALLOC);
	j = 0;
	while (j < count)
	{
		new_envp[j] = base_envp[j];
		j++;
	}
	tmp = assigns;
	while (tmp)
	{
		new_envp[j] = ft_strdup((char *)tmp->content);
		j++;
		tmp = tmp->next;
	}
	new_envp[j] = NULL;
	return (new_envp);
}

char	**build_envp_with_assigns(t_env *env_list, t_list *assigns)
{
	char	**base_envp;
	char	**new_envp;
	int		count;
	int		i;
	t_list	*tmp;

	base_envp = env_list_to_envp(env_list);
	count = 0;
	while (base_envp && base_envp[count])
		count++;
	i = 0;
	tmp = assigns;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	new_envp = create_new_envp_array(base_envp, count, assigns, i);
	free(base_envp);
	return (new_envp);
}

void	create_temporary_assigns(t_list *tmp, t_data *data, char *equal)
{
	char	*key;
	char	*value;
	t_env	*node;

		key = ft_substr((char *)tmp->content, 0,
				equal - (char *)tmp->content);
		value = ft_strdup(equal + 1);
		if (update_existing_env(data->env_list, key, value))
		{
			node = data->env_list;
			while (node)
			{
				if (!ft_strcmp(node->key, key))
				{
					node->is_exported = 1;
					break ;
				}
				node = node->next;
			}
		}
		else
			add_env_back(&data->env_list, new_env(key, value, 1));
		free_key_value(key, value);
}


void	export_temporary_assigns(t_list *assigns, t_data *data)
{
	t_list	*tmp;
	char	*equal;
	// char	*key;
	// char	*value;
	// t_env	*node;

	tmp = assigns;
	while (tmp)
	{
		equal = ft_strchr((char *)tmp->content, '=');
		if (equal)
		{
			create_temporary_assigns(tmp, data, equal);
		// 	key = ft_substr((char *)tmp->content, 0,
		// 			equal - (char *)tmp->content);
		// 	value = ft_strdup(equal + 1);
		// 	if (update_existing_env(data->env_list, key, value))
		// 	{
		// 		node = data->env_list;
		// 		while (node)
		// 		{
		// 			if (!ft_strcmp(node->key, key))
		// 			{
		// 				node->is_exported = 1;
		// 				break ;
		// 			}
		// 			node = node->next;
		// 		}
		// 	}
			// else
			// 	add_env_back(&data->env_list, new_env(key, value, 1));
			// free_key_value(key, value);
		}
		tmp = tmp->next;
	}
}
