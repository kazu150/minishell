/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:32:14 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/15 14:54:54 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_error_exit(char *cmd)
{
	char	*str;
	int		len;

	str = ft_strjoin(cmd, ": No such file or directory\n");
	if (!str)
		error_exit(MALLOC);
	free(cmd);
	len = ft_strlen(str);
	write(2, str, len);
	free(str);
	exit(127);
}

char	**env_list_to_envp(t_env *env_list)
{
	t_env	*list_current;
	int		count;
	int		i;
	char	**envp;

	count = 0;
	i = 0;
	list_current = env_list;
	while (env_list)
	{
		count++;
		env_list = env_list->next;
	}
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	while (list_current)
	{
		envp[i] = ft_strjoin(list_current->key, "=");
		envp[i] = ft_strjoin(envp[i], list_current->value);
		i++;
		list_current = list_current->next;
	}
	envp[i] = 0;
	return (envp);
}

int	execute(t_cmd *cmds, t_env *env_list)
{
	char	*cmd;
	char	**envp;

	if (cmds->args[0] == NULL)
		handle_command_path_error(cmds, 1, 0);
	cmd = build_command_path(cmds, &env_list);
	envp = env_list_to_envp(env_list);
	if (execve(cmd, cmds->args, envp) == -1)
	{
		(free(cmds->args), execve_error_exit(cmd));
	}
	return (0);
}

int	is_redir(char *arg)
{
	if (ft_strncmp(arg, "<", 2) == 0)
		return (1);
	if (ft_strncmp(arg, ">", 2) == 0)
		return (1);
	if (ft_strncmp(arg, "<<", 3) == 0)
		return (1);
	if (ft_strncmp(arg, ">>", 3) == 0)
		return (1);
	return (0);
}

void	sig_int_handler(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
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

t_cmd	*get_cmds_from_readline(t_env **env_list, t_cmd **cmds,
		t_cmd **cmds_first)
{
	char	*line;

	*cmds = NULL;
	*cmds_first = NULL;
	line = NULL;
	line = readline("> ");
	if (line == NULL)
		ft_exit(*cmds, env_list);
	if (ft_strlen(line) == 0)
	{
		free(line);
		return (NULL);
	}
	add_history(line);
	*cmds = parse_input(line);
	*cmds_first = *cmds;
	free(line);
	return (*cmds);
}

void	parent_process(t_pipe_fds *pipe_fds, pid_t pid,
		int *status)
{
	pipe_fds->prev_read_fd = pipe_fds->pipe_fd[0];
	if (pipe_fds->pipe_fd[1] != -1)
		close(pipe_fds->pipe_fd[1]);
	waitpid(pid, status, 0);
}

int	run_normal_command(t_cmd *cmds, t_pipe_fds *pipe_fds,
		t_env **env_list, int *exit_status)
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
		builtin_status = exec_builtin_fn(cmds, env_list, *exit_status);
		if (builtin_status != -1)
		{
			*exit_status = builtin_status;
			free_cmds(&cmds);
			ft_exit(cmds, env_list);
		}
		expand_redirs(cmds->redirs, *env_list, *exit_status);
		return (execute(cmds, *env_list));
	}
	else
		parent_process(pipe_fds, pid, exit_status);
	return (0);
}

int	run_last_command(t_cmd *cmds, t_pipe_fds *pipe_fds,
		t_env **env_list, int *exit_status)
{
	pid_t	pid;
	int		builtin_status;

	builtin_status = exec_builtin_fn(cmds, env_list, *exit_status);
	if (builtin_status != -1)
	{
		*exit_status = builtin_status;
		return (0);
	}
	pid = fork();
	if (pid == -1)
		error_exit(FORK);
	if (pid == 0)
	{
		if (!cmds->redirs)
			connect_pipe(cmds, pipe_fds);
		expand_redirs(cmds->redirs, *env_list, *exit_status);
		return (execute(cmds, *env_list));
	}
	else
		parent_process(pipe_fds, pid, exit_status);
	return (0);
}

void	initialize(t_pipe_fds *pipe_fds, int *exit_status,
		t_env **env_list)
{
	pipe_fds->pipe_fd[0] = -1;
	pipe_fds->pipe_fd[1] = -1;
	pipe_fds->prev_read_fd = -1;
	*exit_status = 0;
	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, SIG_IGN);
	*env_list = init_env();
}

void	readline_roop(t_pipe_fds *pipe_fds, int *exit_status,
		t_env **env_list)
{
	t_cmd	*cmds;
	t_cmd	*cmds_first;

	while (1)
	{
		get_cmds_from_readline(env_list, &cmds, &cmds_first);
		while (cmds)
		{
			if (cmds->next)
				run_normal_command(cmds, pipe_fds, env_list,
					exit_status);
			else
				run_last_command(cmds, pipe_fds, env_list,
					exit_status);
			cmds = cmds->next;
		}
		free_cmds(&cmds_first);
	}
}

int	main(void)
{
	t_pipe_fds	pipe_fds;
	t_env		*env_list;
	int			exit_status;

	initialize(&pipe_fds, &exit_status, &env_list);
	readline_roop(&pipe_fds, &exit_status, &env_list);
	return (0);
}
