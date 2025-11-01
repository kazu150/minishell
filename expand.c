/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:53:03 by cyang             #+#    #+#             */
/*   Updated: 2025/11/01 13:55:38 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_dolloar_question(char *result, int exit_status)
{
	char	*num;
	char	*joined;

	num = ft_itoa(exit_status);
	if (!num)
		error_exit(MALLOC);
	joined = ft_strjoin(result, num);
	free(result);
	free(num);
	if (!joined)
		error_exit(MALLOC);
	return (joined);
}

char	*expand_with_var(char *str, t_env *env_list, int exit_status)
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
			if (str[var_start] == '?')
			{
				var_end = var_start + 1;
				result = handle_dolloar_question(result, exit_status);
				result = add_after_var(result, str, var_end, env_list,
						exit_status);
				break ;
			}
			var_end = var_start;
			while (str[var_end] && (ft_isalnum(str[var_end])
					|| str[var_end] == '_'))
				var_end++;
			result = expand_and_add_var(result, str, var_start, var_end,
					env_list);
			result = add_after_var(result, str, var_end, env_list, exit_status);
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
char	*expand_token(char *str, t_env *env_list, int exit_status)
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
		transform = expand_with_var(without_quote, env_list, exit_status);
		return (transform);
	}
	// "$FOO" → bar
	else if (!ft_strchr(str, '\'') && !ft_strchr(str, '\"') && ft_strchr(str,
			'$'))
	{
		transform = expand_with_var(str, env_list, exit_status);
		return (transform);
	}
	return (str);
}

char	**expand_all(char **strs, t_env *env_list, int exit_status)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		strs[i] = expand_token(strs[i], env_list, exit_status);
		i++;
	}
	return (strs);
}

char	**expand_args(char **args, t_env *env_list, int exit_status)
{
	args = expand_all(args, env_list, exit_status);
	return (args);
}

int find_unused_fd(int fd, t_fds fds)
{
	int new_fd;
	new_fd = fd + 1;

	if (fds.read_fd == new_fd)
		new_fd++;
	if (fds.write_fd == new_fd)
		new_fd++;
	return new_fd;
}

t_fds	expand_redirs(t_redir *redirs, t_env *env_list, int exit_status)
{
	int		fd;
	char	*target;
	t_fds	fds;

	// char		*cmd;
	while (redirs)
	{
		if (redirs->type == R_IN || redirs->type == R_HDOC)
		{
			target = expand_token(redirs->target, env_list, exit_status);
			if (redirs->type == R_IN)
				fd = open(target, O_RDONLY);
			else if (redirs->type == R_HDOC)
				fd = setup_heredoc(redirs->target);
			if (fd == -1)
				error_exit(target);
			fds.read_fd = find_unused_fd(fd, fds);
			dup2(STDIN_FILENO, fds.read_fd);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redirs->type == R_OUT || redirs->type == R_APP)
		{
			if (redirs->type == R_OUT)
				fd = open(expand_token(redirs->target, env_list, exit_status),
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (redirs->type == R_APP)
				fd = open(expand_token(redirs->target, env_list, exit_status),
						O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				error_exit(target);
			fds.write_fd = find_unused_fd(fd, fds);
			dup2(STDOUT_FILENO, fds.write_fd);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redirs = redirs->next;
	}
	return fds;
}
