/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 07:39:06 by cyang             #+#    #+#             */
/*   Updated: 2025/10/19 15:46:03 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*store_before_dollor(char *result, char *str, int dollar_pos)
{
	char	*tmp;
	char	*new_result;

	if (dollar_pos > 0)
	{
		tmp = ft_substr(str, 0, dollar_pos);
		new_result = ft_strjoin(result, tmp);
		free(result);
		free(tmp);
		return (new_result);
	}
	return (result);
}

char	*ft_getenv(t_env *env_list, char *key)
{
	t_env	*current = env_list;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*expand_and_add_var(char *result, char *str, int var_start, int var_end, t_env *env_list)
{
	char	*key_name;
	char	*key_value;
	char	*tmp;

	if (var_end > var_start)
	{
		key_name = ft_substr(str, var_start, var_end - var_start);
		key_value = ft_getenv(env_list, key_name);
		if (key_value)
		{
			tmp = ft_strjoin(result, key_value);
			free(result);
			result = tmp;
		}
		free(key_name);
	}
	else
	{
		tmp = ft_strjoin(result, "$");
		free(result);
		result = tmp;
	}
	return (result);
}

char	*add_after_var(char *result, char *str, int var_end, t_env *env_list, int exit_status)
{
	char	*rest;
	char	*rest_expanded;
	char	*tmp;

	if (str[var_end])
	{
		rest = ft_substr(str, var_end, ft_strlen(str) - var_end);
		rest_expanded = expand_with_var(rest, env_list, exit_status);
		tmp = ft_strjoin(result, rest_expanded);
		free(result);
		free(rest_expanded);
		return (tmp);
	}
	return (result);
}
