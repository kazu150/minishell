/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:41:29 by cyang             #+#    #+#             */
/*   Updated: 2025/11/23 14:49:01 by cyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_process(t_pipe_fds *pipe_fds, pid_t pid, int *exit_status)
{
	// int		status;
	// void	(*old_sigint)(int);
	(void)pid;
	(void)exit_status;

	// old_sigint = signal(SIGINT, SIG_IGN);
	if (pipe_fds->prev_read_fd != -1)
		close(pipe_fds->prev_read_fd);
	pipe_fds->prev_read_fd = pipe_fds->pipe_fd[0];
	if (pipe_fds->pipe_fd[1] != -1)
		close(pipe_fds->pipe_fd[1]);

	// waitpid(pid, &status, 0);
	// signal(SIGINT, old_sigint);
	// *exit_status = status >> 8;
}

void	connect_pipe(t_cmd *cmds, t_pipe_fds *pipe_fds)
{
	if (pipe_fds->prev_read_fd != -1)
	{
		dup2(pipe_fds->prev_read_fd, STDIN_FILENO);
		close(pipe_fds->prev_read_fd);
	}
	if (cmds->next)
	{
		dup2(pipe_fds->pipe_fd[1], STDOUT_FILENO);
	}
	if (pipe_fds->pipe_fd[0] != -1)
		close(pipe_fds->pipe_fd[0]);
	if (pipe_fds->pipe_fd[1] != -1)
		close(pipe_fds->pipe_fd[1]);
}
