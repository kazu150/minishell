/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 18:39:47 by cyang             #+#    #+#             */
/*   Updated: 2025/11/04 14:09:43 by cyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_valid_export_key(const char *key)
{
	int	i;

	if (!key || !key[0])
		return (0);
	//一つ目の文字は必ずアルファベットか＿
	if (!(ft_isalpha((unsigned char)key[0]) || key[0] == '_'))
		return (0);
	i = 1;
	//2つ目以降の文字はアルファベット、＿可
	while (key[i])
	{
		if (!(ft_isalnum((unsigned char)key[i]) || key[i] == '_'))
		return (0);
		i++;
	}
	return (1);
}

static int	handle_export_error(char *invalid_key)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(invalid_key, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (1);
}

static int	handle_no_equal_case(char *arg)
{
	if (!is_valid_export_key(arg))
		return (handle_export_error(arg));
	return (0);
}
static int	update_existing_env(t_env *env_list, char *key, char *value)
{
	t_env *current;

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

static void	free_key_value(char *key, char *value)
{
	free(key);
	free(value);
}

static int	process_key_value(char *arg, t_env **env_list)
{
	char	*equal_pos;
	char 	*key;
	char	*value;
	int		exit_code;

	equal_pos = ft_strchr(arg, '=');
	if (!equal_pos)
		return (handle_no_equal_case(arg));
	if (equal_pos == arg)
		return (handle_export_error(arg));
	key = ft_substr(arg, 0, equal_pos - arg);
	value = ft_strdup(equal_pos + 1);
	if (!key || !value)
	{
		free_key_value(key, value);
		return (1);
	}
	if (!is_valid_export_key(key))
	{
		exit_code = handle_export_error(arg);
		free_key_value(key, value);
		return (exit_code);
	}
	if (!update_existing_env(*env_list, key, value))
		add_env_back(env_list, new_env(key, value));
	free_key_value(key, value);
	return (0);
}

int	ft_export(char **args, t_env **env_list)
{
	int		i;
	int		exit_code;
	int		result;

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
