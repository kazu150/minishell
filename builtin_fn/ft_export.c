/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 18:39:47 by cyang             #+#    #+#             */
/*   Updated: 2025/11/22 16:15:21 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_no_equal_case(char *arg, t_env *env_list)
{
	t_env	*target;

	if (!is_valid_export_key(arg))
		return (handle_export_error(arg));
	target = env_list;
	while (target)
	{
		if (ft_strcmp(target->key, arg) == 0)
		{
			target->is_exported = 1;
			return (0);
		}
		target = target->next;
	}
	add_env_back(&env_list, new_env(arg, NULL, 1));
	return (0);
}

static int	process_key_value(char *arg, t_env **env_list)
{
	char	*equal_pos;
	char	*key;
	char	*value;
	int		exit_code;

	equal_pos = ft_strchr(arg, '=');
	if (!equal_pos)
		return (handle_no_equal_case(arg, *env_list));
	if (equal_pos == arg)
		return (handle_export_error(arg));
	key = ft_substr(arg, 0, equal_pos - arg);
	value = ft_strdup(equal_pos + 1);
	if (!key || !value)
		return (free_key_value(key, value), 1);
	if (!is_valid_export_key(key))
	{
		exit_code = handle_export_error(arg);
		free_key_value(key, value);
		return (exit_code);
	}
	update_env_list(env_list, key, value);
	return (free_key_value(key, value), 0);
}

static t_env	*find_next_min(t_env *env_list, char *last_key)
{
	t_env	*current;
	t_env	*min_env;

	min_env = NULL;
	current = env_list;
	while (current)
	{
		if (current->is_exported && (last_key == NULL || ft_strcmp(current->key,
					last_key) > 0))
		{
			if (min_env == NULL || ft_strcmp(current->key, min_env->key) < 0)
				min_env = current;
		}
		current = current->next;
	}
	return (min_env);
}

static void	print_exported_env(t_env *env_list)
{
	t_env	*next;
	char	*last_key;

	if (!env_list)
		return ;
	last_key = NULL;
	while (1)
	{
		next = find_next_min(env_list, last_key);
		if (!next)
			break ;
		if (next->value && next->value[0] != '\0')
			printf("declare -x %s=\"%s\"\n", next->key, next->value);
		else
			printf("declare -x %s\n", next->key);
		last_key = next->key;
	}
}

int	ft_export(char **args, t_env **env_list)
{
	int	i;
	int	exit_code;
	int	result;

	if (!args || !args[1])
	{
		print_exported_env(*env_list);
		return (0);
	}
	i = 1;
	exit_code = 0;
	while (args[i])
	{
		result = process_key_value(args[i], env_list);
		if (result != 0)
			exit_code = result;
		i++;
	}
	return (exit_code);
}
