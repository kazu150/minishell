/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:53:03 by cyang             #+#    #+#             */
/*   Updated: 2025/11/16 14:42:44 by cyang            ###   ########.fr       */
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
	t_var	var;

	result = ft_strdup("");
	if (!result)
		error_exit(MALLOC);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			result = store_before_dollor(result, str, i);
			var.start = i + 1;
			if (str[var.start] == '?')
			{
				var.end = var.start + 1;
				result = handle_dolloar_question(result, exit_status);
				result = add_after_var(result, str, var.end, env_list,
						exit_status);
				break ;
			}
			var.end = var.start;
			while (str[var.end] && (ft_isalnum(str[var.end])
					|| str[var.end] == '_'))
				var.end++;
			result = expand_and_add_var(result, str, var,
					env_list);
			result = add_after_var(result, str, var.end, env_list, exit_status);
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
	return (result);
}

char	*expand_token(char *str, t_env *env_list, int exit_status)
{
	int		len;
	char	*transform;
	char	*without_quote;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if ((str[0] == '\'' && str[len - 1] == '\'') || (str[0] == '\"' && str[len
			- 1] == '\"' && !ft_strchr(str, '$')))
	{
		transform = ft_substr(str, 1, len - 2);
		return (transform);
	}
	if (str[0] == '\"' && str[len - 1] == '\"' && ft_strchr(str, '$'))
	{
		without_quote = ft_substr(str, 1, len - 2);
		transform = expand_with_var(without_quote, env_list, exit_status);
		free(without_quote);
		return (transform);
	}
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
	char	*old;
	char	*expanded;

	i = 0;
	while (strs[i])
	{
		old = strs[i];
		expanded = expand_token(strs[i], env_list, exit_status);
		if (expanded != old)
		{
			free(old);
			strs[i] = expanded;
		}
		else
			strs[i] = old;
		i++;
	}
	return (strs);
}

char	**expand_args(char **args, t_env *env_list, int exit_status)
{
	args = expand_all(args, env_list, exit_status);
	return (args);
}

int	find_unused_fd(int fd, t_fds fds)
{
	int	new_fd;

	new_fd = fd + 1;
	if (fds.read_fd == new_fd)
		new_fd++;
	if (fds.write_fd == new_fd)
		new_fd++;
	return (new_fd);
}

t_fds	expand_redirs(t_redir *redirs, t_env *env_list, int exit_status)
{
	int		fd;
	char	*target;
	t_fds	fds;

	target = NULL;
	fd = 0;
	fds.read_fd = -1;
	fds.write_fd = -1;
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
			{
				// error_exit(target);
				perror(target);
					free(target);
				exit(1);
			}
				
			fds.read_fd = find_unused_fd(fd, fds);
			dup2(STDIN_FILENO, fds.read_fd);
			dup2(fd, STDIN_FILENO);
			close(fd);
			if (target != redirs->target)
				free(target);
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
			{
				perror(target);
				if (target != redirs->target)
					free(target);
				exit(1);
			}
			fds.write_fd = find_unused_fd(fd, fds);
			dup2(STDOUT_FILENO, fds.write_fd);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			if (target != redirs->target)
				free(target);
		}
		redirs = redirs->next;
	}
	return (fds);
}
