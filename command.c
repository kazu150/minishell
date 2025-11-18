/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:34:41 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/17 03:36:47 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute(t_cmd *cmds, t_env *env_list)
{
	char	*cmd;
	char	**envp;

	if (!cmds->args || cmds->args[0] == NULL)
	{
		if (cmds->redirs)
			exit(0);
		else
			handle_command_path_error(cmds, 1, 0);
	}
	cmd = build_command_path(cmds, &env_list);
	envp = env_list_to_envp(env_list);
	if (execve(cmd, cmds->args, envp) == -1)
	{
		free_all(envp);
		execve_error_exit(cmd);
	}
	return (0);
}

static void	connect_pipe(t_cmd *cmds, t_pipe_fds *pipe_fds)
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

void	parent_process(t_pipe_fds *pipe_fds, pid_t pid, int *exit_status)
{
	int	status;

	pipe_fds->prev_read_fd = pipe_fds->pipe_fd[0];
	if (pipe_fds->pipe_fd[1] != -1)
		close(pipe_fds->pipe_fd[1]);
	waitpid(pid, &status, 0);
	*exit_status = status >> 8;
}

int	run_normal_command(t_cmd *cmds, t_pipe_fds *pipe_fds, t_data *data)
{
	pid_t	pid;
	int		builtin_status;

	pipe(pipe_fds->pipe_fd);
	pid = fork();
	if (pid == -1)
		error_exit(FORK);
	if (pid == 0)
	{
		if (!cmds->redirs)
			connect_pipe(cmds, pipe_fds);
		builtin_status = exec_builtin_fn(cmds, data);
		if (builtin_status != -1)
		{
			data->exit_status = builtin_status;
			// free_cmds(cmds);
			// ft_exit(cmds, data);
			exit(builtin_status);
		}
		expand_redirs(cmds->redirs, data);
		return (execute(cmds, data->env_list));
	}
	else
		parent_process(pipe_fds, pid, &data->exit_status);
	return (0);
}

int	run_last_command(t_cmd *cmds, t_pipe_fds *pipe_fds, t_data *data)
{
	pid_t	pid;
	int		builtin_status;

	builtin_status = exec_builtin_fn(cmds, data);
	if (builtin_status != -1)
	{
		data->exit_status = builtin_status;
		return (0);
	}
	pid = fork();
	if (pid == -1)
		error_exit(FORK);
	if (pid == 0)
	{
		if (!cmds->redirs)
			connect_pipe(cmds, pipe_fds);
		expand_redirs(cmds->redirs, data);
		return (execute(cmds, data->env_list));
	}
	else
		parent_process(pipe_fds, pid, &data->exit_status);
	return (0);
}
