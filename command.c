/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:34:41 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/21 18:26:51 by cyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_assignment_only(t_list *assigns, t_data *data)
{
	char	*equal;
	char	*key;
	char	*value;
	t_list	*tmp;

	tmp = assigns;
	while (tmp)
	{
		equal = ft_strchr((char *)tmp->content, '=');
		if (equal)
		{
			key = ft_substr((char *)tmp->content, 0, equal - (char *)tmp->content);
			value = ft_strdup(equal + 1);
			if (!update_existing_env(data->env_list, key, value))
				add_env_back(&data->env_list, new_env(key, value, 0));
			free_key_value(key, value);
		}
		tmp = tmp->next;
	}
}

static char	**build_envp_with_assigns(t_env *env_list, t_list *assigns)
{
	char	**base_envp;
	char	**new_envp;
	int		count;
	int		i;
	int		j;
	t_list 	*tmp;

	base_envp = env_list_to_envp(env_list);
	count = 0;
	while (base_envp && base_envp[count])
		count++;
	i = 0;
	tmp = assigns;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	new_envp = malloc(sizeof(char *) * (count + i + 1));
	if (!new_envp)
		error_exit(MALLOC);
	j = 0;
	while (j < count)
	{
		new_envp[j] = base_envp[j];
		j++;
	}
	free(base_envp);
	tmp = assigns;
	while (tmp)
	{
		new_envp[j] = ft_strdup((char *)tmp->content);
		j++;
		tmp = tmp->next;
	}
	new_envp[j] = NULL;
	return (new_envp);
}

static void	export_temporary_assigns(t_list *assigns, t_data *data)
{
	t_list	*tmp;
	char	*equal;
	char	*key;
	char	*value;
	t_env	*node;

	tmp = assigns;
	while (tmp)
	{
		equal = ft_strchr((char *)tmp->content, '=');
		if (equal)
		{
			key = ft_substr((char *)tmp->content, 0, equal - (char *)tmp->content);
			value = ft_strdup(equal + 1);
			if (update_existing_env(data->env_list, key, value))
			{
				node = data->env_list;
				while (node)
				{
					if (!ft_strcmp(node->key, key))
					{
						node->is_exported = 1;
						break;
					}
					node = node->next;
				}
			}
			else
				add_env_back(&data->env_list, new_env(key, value, 1));
			free_key_value(key, value);
		}
		tmp = tmp->next;
	}
}

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
	cmd = build_command_path(cmds, &env_list, 0, 0);
	envp = build_envp_with_assigns(env_list, cmds->assigns);
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
	int		status;
	void	(*old_sigint)(int);

	old_sigint = signal(SIGINT, SIG_IGN);
	pipe_fds->prev_read_fd = pipe_fds->pipe_fd[0];
	if (pipe_fds->pipe_fd[1] != -1)
		close(pipe_fds->pipe_fd[1]);
	waitpid(pid, &status, 0);
	signal(SIGINT, old_sigint);
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
		set_default_signals();
		g_sigint_received = 0;
		if (!cmds->redirs)
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
	else
		parent_process(pipe_fds, pid, &data->exit_status);
	return (0);
}

int	run_last_command(t_cmd *cmds, t_pipe_fds *pipe_fds, t_data *data)
{
	pid_t	pid;
	int		builtin_status;

	if (pipe_fds->prev_read_fd == -1)
	{
		if (!cmds->args || !cmds->args[0])
		{
			expand_redirs(cmds->redirs, data);
			if (cmds->assigns)
				handle_assignment_only(cmds->assigns, data);
			return (0);
		}
		builtin_status = exec_builtin_fn(cmds, data);
		if (builtin_status != -1)
		{
			data->exit_status = builtin_status;
			return (0);
		}
	}
	pid = fork();
	if (pid == -1)
		error_exit(FORK);
	if (pid == 0)
	{
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
		if (!cmds->redirs)
			connect_pipe(cmds, pipe_fds);
		expand_redirs(cmds->redirs, data);
		return (execute(cmds, data->env_list));
	}
	else
		parent_process(pipe_fds, pid, &data->exit_status);
	return (0);
}
