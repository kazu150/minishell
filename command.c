/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:34:41 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/22 16:08:34 by cyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	run_normal_command_child(t_cmd *cmds, t_pipe_fds *pipe_fds,
	t_data *data)
{
	int	builtin_status;

	set_default_signals();
	g_sigint_received = 0;
	connect_pipe(cmds, pipe_fds);
	if (!cmds->args || !cmds->args[0])
	{
		expand_redirs(cmds->redirs, data);
		exit(0);
	}
	if (cmds->assigns)
		export_temporary_assigns(cmds->assigns, data);
	builtin_status = exec_builtin_fn(cmds, data);
	if (builtin_status != -1)
	{
		data->exit_status = builtin_status;
		free_cmds(&cmds);
		exit(builtin_status);
	}
	expand_redirs(cmds->redirs, data);
	return (execute(cmds, data->env_list));
}

int	run_normal_command(t_cmd *cmds, t_pipe_fds *pipe_fds, t_data *data)
{
	pid_t	pid;

	pipe(pipe_fds->pipe_fd);
	pid = fork();
	if (pid == -1)
		error_exit(FORK);
	if (pid == 0)
		run_normal_command_child(cmds, pipe_fds, data);
	else
		parent_process(pipe_fds, pid, &data->exit_status);
	return (0);
}

static void	builtin_without_pipe(t_cmd *cmds, t_data *data)
{
	int	builtin_status;

	if (!cmds->args || !cmds->args[0])
	{
		expand_redirs(cmds->redirs, data);
		if (cmds->assigns)
			handle_assignment_only(cmds->assigns, data);
		return ;
	}
	builtin_status = exec_builtin_fn(cmds, data);
	if (builtin_status != -1)
	{
		data->exit_status = builtin_status;
		return ;
	}
}

int	run_last_command_child(t_cmd *cmds, t_pipe_fds *pipe_fds, t_data *data)
{
	int		builtin_status;

	set_default_signals();
	g_sigint_received = 0;
	if (pipe_fds->prev_read_fd != -1)
	{
		if (cmds->assigns)
			export_temporary_assigns(cmds->assigns, data);
		builtin_status = exec_builtin_fn(cmds, data);
		if (builtin_status != -1)
		{
			data->exit_status = builtin_status;
			exit(builtin_status);
		}
	}
	connect_pipe(cmds, pipe_fds);
	expand_redirs(cmds->redirs, data);
	return (execute(cmds, data->env_list));
}

int	run_last_command(t_cmd *cmds, t_pipe_fds *pipe_fds, t_data *data)
{
	pid_t	pid;

	if (pipe_fds->prev_read_fd == -1)
		builtin_without_pipe(cmds, data);
	pid = fork();
	if (pid == -1)
		error_exit(FORK);
	if (pid == 0)
		run_last_command_child(cmds, pipe_fds, data);
	else
		parent_process(pipe_fds, pid, &data->exit_status);
	return (0);
}
