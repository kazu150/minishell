/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 18:39:47 by cyang             #+#    #+#             */
/*   Updated: 2025/10/27 13:55:50 by cyang            ###   ########.fr       */
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
int	ft_export(char **args, t_env **env_list)
{
	t_env	*current;
	int		i;
	int		exist;
	char	*equal_pos;
	char	*key;
	char	*value;
	int		exit_code;

	i = 1;
	exit_code = 0;
	while (args[i])
	{
		equal_pos = ft_strchr(args[i], '=');
		if (!equal_pos)
		{
			if (!is_valid_export_key(args[i]))
				exit_code = handle_export_error(args[i]);
			i++;
			continue ;
		}
		if (equal_pos == args[i])
		{
			ft_putendl_fd("export: =: not a valid identifier", 2);
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
		if (!is_valid_export_key(key))
		{
			exit_code = handle_export_error(args[i]);
			free(key);
			free(value);
			i++;
			continue ;
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
	return (exit_code);
}
