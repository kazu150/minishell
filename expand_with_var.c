/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_with_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 13:54:04 by codespace         #+#    #+#             */
/*   Updated: 2025/11/23 13:05:51 by cyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_double_quoted_with_vars(char *str, t_data *data)
{
	return (expand_with_var(str, data));
}

char	*expand_token(char *str, t_data *data)
{
	int		len;
	char	*transform;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (str[0] == '\"' && str[len - 1] == '\"' && ft_strchr(str, '$'))
		return (expand_double_quoted_with_vars(str, data));
	else if (!ft_strchr(str, '\'') && !ft_strchr(str, '\"') && ft_strchr(str,
			'$'))
	{
		transform = expand_with_var(str, data);
		return (transform);
	}
	return (str);
}

static char	*process_dollar_variable(char *str, int i, char *result,
	t_data *data)
{
	t_var	var;

	result = store_before_dollor(result, str, i);
	var.start = i + 1;
	if (str[var.start] == '?')
	{
		var.end = var.start + 1;
		result = handle_dolloar_question(result, data);
		result = add_after_var(result, str, var.end, data);
		return (result);
	}
	var.end = var.start;
	while (str[var.end] && (ft_isalnum(str[var.end]) || str[var.end] == '_'))
		var.end++;
	result = expand_and_add_var(result, str, var, data->env_list);
	result = add_after_var(result, str, var.end, data);
	return (result);
}

char	*expand_with_var(char *str, t_data *data)
{
	char	*result;
	char	*tmp;
	int		i;

	result = ft_strdup("");
	if (!result)
		error_exit(MALLOC);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			result = process_dollar_variable(str, i, result, data);
			return (result);
		}
		i++;
	}
	tmp = ft_strjoin(result, str);
	free(result);
	return (tmp);
}
