/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 07:39:06 by cyang             #+#    #+#             */
/*   Updated: 2025/11/17 02:11:02 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_and_add_var(char *result, char *str, t_var var, t_env *env_list)
{
	char	*key_name;
	char	*key_value;
	char	*tmp;

	if (var.end > var.start)
	{
		key_name = ft_substr(str, var.start, var.end - var.start);
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

char	*add_after_var(char *result, char *str, int var_end, t_data *data)
{
	char	*rest;
	char	*rest_expanded;
	char	*tmp;

	if (str[var_end])
	{
		rest = ft_substr(str, var_end, ft_strlen(str) - var_end);
		rest_expanded = expand_with_var(rest, data);
		tmp = ft_strjoin(result, rest_expanded);
		free(result);
		free(rest_expanded);
		free(rest);
		return (tmp);
	}
	return (result);
}

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

char	*handle_dolloar_question(char *result, t_data *data)
{
	char	*num;
	char	*joined;

	num = ft_itoa(data->exit_status);
	if (!num)
		error_exit(MALLOC);
	joined = ft_strjoin(result, num);
	free(result);
	free(num);
	if (!joined)
		error_exit(MALLOC);
	return (joined);
}

char	**expand_args(char **args, t_data *data)
{
	args = expand_all(args, data);
	return (args);
}
