/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:53:03 by cyang             #+#    #+#             */
/*   Updated: 2025/10/06 07:47:24 by cyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
char	*expand_token(char *str)
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
		strs[i] = expand_token(strs[i]);
		i++;
	}
	return (strs);
}

char	**expand(char **args, t_redir *redirs)
{
	// char		*cmd;
	int			fd;
	char		*target;

	while (redirs)
	{
		if (redirs->type == R_IN || redirs->type == R_HDOC)
		{
			target = expand_token(redirs->target);
			if (redirs->type == R_IN)
				fd = open(target, O_RDONLY);
			else if (redirs->type == R_HDOC)
				fd = setup_heredoc(redirs->target);
			if (fd == -1)
				(free_split(args), error_exit(target));
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redirs->type == R_OUT || redirs->type == R_APP)
		{
			if (redirs->type == R_OUT)
				fd = open(expand_token(redirs->target), O_WRONLY | O_CREAT | O_TRUNC,
						0644);
			else if (redirs->type == R_APP)
				fd = open(expand_token(redirs->target), O_WRONLY | O_CREAT | O_APPEND,
						0644);
			if (fd == -1)
				(free_split(args), error_exit(target));
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redirs = redirs->next;
	}
	args = expand_all(args);
	return (args);
}