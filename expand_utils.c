/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 07:39:06 by cyang             #+#    #+#             */
/*   Updated: 2025/10/06 07:40:36 by cyang            ###   ########.fr       */
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

char	*expand_and_add_var(char *result, char *str, int var_start, int var_end)
{
	char	*var_name;
	char	*var_value;
	char	*tmp;

	if (var_end > var_start)
	{
		var_name = ft_substr(str, var_start, var_end - var_start);
		var_value = getenv(var_name);
		if (var_value)
		{
			tmp = ft_strjoin(result, var_value);
			free(result);
			result = tmp;
		}
		free(var_name);
	}
	else
	{
		tmp = ft_strjoin(result, "$");
		free(result);
		result = tmp;
	}
	return (result);
}

char	*add_after_var(char *result, char *str, int var_end)
{
	char	*rest;
	char	*rest_expanded;
	char	*tmp;

	if (str[var_end])
	{
		rest = ft_substr(str, var_end, ft_strlen(str) - var_end);
		rest_expanded = expand_with_var(rest);
		tmp = ft_strjoin(result, rest_expanded);
		free(result);
		free(rest_expanded);
		return (tmp);
	}
	return (result);
}