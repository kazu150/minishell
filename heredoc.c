/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:55:23 by kaisogai          #+#    #+#             */
/*   Updated: 2025/09/27 17:35:00 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	write_all(int fd, const void *buf, size_t len)
{
	const char	*p = buf;
	ssize_t		w;

	while (len > 0)
	{
		w = write(fd, p, len);
		if (w < 0)
		{
			if (errno == EINTR)
				continue ;
			return (-1);
		}
		p += (size_t)w;
		len -= (size_t)w;
	}
	return (0);
}

int	setup_heredoc(char *target)
{
	char	*line;
	int		fds[2];

	pipe(fds);
	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL)
		{ // Ctrl-D / EOF
			// bash 互換にするなら警告を出してもよい
			break ;
		}
		if (ft_strncmp(target, line, ft_strlen(target)) == 0)
		{ // 完全一致で終了
			free(line);
			break ;
		}
		// 行 → 書き端（改行を付与）
		if (write_all(fds[1], line, strlen(line)) < 0 || write_all(fds[1], "\n",
				1) < 0)
		{
			free(line);
			close(fds[0]);
			close(fds[1]);
			return (-1);
		}
		free(line);
	}
	close(fds[1]);
	return (fds[0]);
}
