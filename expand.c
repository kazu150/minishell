/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:53:03 by cyang             #+#    #+#             */
/*   Updated: 2025/11/21 19:31:53 by cyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_quotes(char *s)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	quote;
	char	*res;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	res = malloc(len + 1);
	if (!res)
		return (ft_strdup(s));
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				res[j++] = s[i++];
			if (s[i] == quote)
				i++;
		}
		else
			res[j++] = s[i++];
	}
	res[j] = '\0';
	return (res);
}

char	**expand_all(char **strs, t_data *data)
{
	int		i;
	char	*old;
	char	*expanded;
	char	*clean;

	i = 0;
	while (strs[i])
	{
		old = strs[i];
		expanded = expand_token(old, data);
		if (expanded != old)
		{
			clean = remove_quotes(expanded);
			free(expanded);
			free(old);
			strs[i] = clean;
		}
		else
		{
			clean = remove_quotes(old);
			free(old);
			strs[i] = clean;
		}
		i++;
	}
	return (strs);
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

static int	handle_input_redir(t_redir *redirs, t_data *data, t_fds *fds)
{
	int		fd;
	char	*target;

	fd = 0;
	target = expand_token(redirs->target, data);
	if (redirs->type == R_IN)
		fd = open(target, O_RDONLY);
	else if (redirs->type == R_HDOC)
		fd = setup_heredoc(redirs->target, redirs->heredoc_quote, data);
	if (fd == -1)
	{
		perror(target);
		free(target);
		exit(1);
	}
	fds->read_fd = find_unused_fd(fd, *fds);
	dup2(STDIN_FILENO, fds->read_fd);
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (target != redirs->target)
		free(target);
	return (0);
}

static int	handle_output_redir(t_redir *redirs, t_data *data, t_fds *fds)
{
	int		fd;
	char	*target;

	fd = 0;
	target = expand_token(redirs->target, data);
	if (redirs->type == R_OUT)
		fd = open(target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redirs->type == R_APP)
		fd = open(target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(target);
		if (target != redirs->target)
			free(target);
		exit(1);
	}
	fds->write_fd = find_unused_fd(fd, *fds);
	dup2(STDOUT_FILENO, fds->write_fd);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (target != redirs->target)
		free(target);
	return (0);
}

t_fds	expand_redirs(t_redir *redirs, t_data *data)
{
	int		fd;
	char	*target;
	t_fds	fds;

	(void)fd;
	(void)target;
	fds.read_fd = -1;
	fds.write_fd = -1;
	while (redirs)
	{
		if (redirs->type == R_IN || redirs->type == R_HDOC)
			handle_input_redir(redirs, data, &fds);
		else if (redirs->type == R_OUT || redirs->type == R_APP)
			handle_output_redir(redirs, data, &fds);
		redirs = redirs->next;
	}
	return (fds);
}
