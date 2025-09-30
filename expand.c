/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:53:03 by cyang             #+#    #+#             */
/*   Updated: 2025/09/30 13:53:05 by cyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*store_before_dollor(char *result, char *str, int dollar_pos)
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

static char	*expand_and_add_var(char *result, char *str, int var_start, int var_end)
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

static char	*add_after_var(char *result, char *str, int var_end)
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

char	*expand_with_var(char *str)
{
	char	*result;
	char	*tmp;
	int		i;
	int		var_start;
	int		var_end;

	result = ft_strdup("");
	if (!result)
		error_exit(MALLOC);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			result = store_before_dollor(result, str, i);
			var_start = i + 1;
			var_end = var_start;
			while (str[var_end] && (ft_isalnum(str[var_end]) || str[var_end] == '_'))
				var_end++;
			result = expand_and_add_var(result, str, var_start, var_end);
			result = add_after_var(result, str, var_end);
			break ;
		}
		i++;
	}
	if (i == (int)ft_strlen(str))
	{
		tmp = ft_strjoin(result, str);
		free(result);
		result = tmp;
	}
	free(str);
	return (result);
}

// TODO
// 例
// "foo" → foo
// $FOO → bar
// '$FOO' → $FOO
// "$FOO" → bar
char	*expand(char *str)
{
	int		len;
	char	*transform;
	char	*without_quote;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	// "foo" → foo & '$FOO' → $FOO
	if ((str[0] == '\'' && str[len - 1] == '\'') || (str[0] == '\"' && str[len
			- 1] == '\"' && !ft_strchr(str, '$')))
	{
		transform = ft_substr(str, 1, len - 2);
		free(str);
		return (transform);
	}
	//"$FOO" → bar && $FOO → bar  home=3 skdjkf$home → skdjkf3
	if (str[0] == '\"' && str[len - 1] == '\"' && ft_strchr(str, '$'))
	{
		without_quote = ft_substr(str, 1, len - 2);
		free(str);
		transform = expand_with_var(without_quote);
		return (transform);
	}
	// "$FOO" → bar
	else if (!ft_strchr(str, '\'') && !ft_strchr(str, '\"') && ft_strchr(str,
			'$'))
	{
		transform = expand_with_var(str);
		return (transform);
	}
	return (str);
}

char	**expand_all(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		strs[i] = expand(strs[i]);
		i++;
	}
	return (strs);
}
