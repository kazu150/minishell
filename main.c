/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:32:14 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/15 11:08:32 by kaisogai         ###   ########.fr       */
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
	envp = malloc(sizeof(char *) * count);
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
// ctrl C　の時
void	sigIntHandler(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();       //　readlineに改行を伝える
	rl_replace_line("", 0); //　USERが入力したバッファーをクリーン
	rl_redisplay();         //　promptを表示しなおす
}

void	connect_pipe(t_cmd *cmds, int pipe_fd[2], int prev_read_fd)
{
	if (prev_read_fd != -1)
	{
		dup2(prev_read_fd, STDIN_FILENO);
		close(prev_read_fd);
	}
	if (cmds->next)
		dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
}

t_cmd	*get_cmds_from_readline(t_env **env_list, t_cmd **cmds,
		t_cmd **cmds_first)
{
	char	*line;

	*cmds = NULL;
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

int	run_normal_command(t_cmd *cmds, int pipe_fd[2], int *prev_read_fd,
		t_env *env_list, int *exit_status, int *status)
{
	pid_t	pid;
	int		builtin_status;

	pipe(pipe_fd);
	pid = fork();
	if (pid == -1)
		error_exit(FORK);
	if (pid == 0)
	{
		if (!cmds->redirs)
			connect_pipe(cmds, pipe_fd, *prev_read_fd);
		builtin_status = exec_builtin_fn(cmds, &env_list, *exit_status);
		if (builtin_status != -1)
		{
			*exit_status = builtin_status;
			free_cmds(cmds);
			ft_exit(cmds, &env_list);
		}
		expand_redirs(cmds->redirs, env_list, *exit_status);
		return (execute(cmds, env_list));
	}
	else
	{
		*prev_read_fd = pipe_fd[0];
		close(pipe_fd[1]);
		waitpid(pid, status, 0);
	}
	return (0);
}

int	run_last_command(t_cmd *cmds, int pipe_fd[2], int *prev_read_fd,
		t_env *env_list, int *exit_status, int *status)
{
	pid_t	pid;
	int		builtin_status;

	builtin_status = exec_builtin_fn(cmds, &env_list, *exit_status);
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
			connect_pipe(cmds, pipe_fd, *prev_read_fd);
		expand_redirs(cmds->redirs, env_list, *exit_status);
		return (execute(cmds, env_list));
	}
	else
	{
		*prev_read_fd = pipe_fd[0];
		close(pipe_fd[1]);
		waitpid(pid, status, 0);
	}
	return (0);
}

int	main(void)
{
	int		prev_read_fd;
	int		pipe_fd[2];
	int		status;
	t_cmd	*cmds;
	t_cmd	*cmds_first;
	t_env	*env_list;
	int		exit_status;

	prev_read_fd = -1;
	exit_status = 0;
	signal(SIGINT, sigIntHandler);
	signal(SIGQUIT, SIG_IGN);
	env_list = init_env();
	while (1)
	{
		get_cmds_from_readline(&env_list, &cmds, &cmds_first);
		while (cmds)
		{
			if (cmds->next)
				run_normal_command(cmds, pipe_fd, &prev_read_fd, env_list, &exit_status, &status);
			else
				run_last_command(cmds, pipe_fd, &prev_read_fd, env_list, &exit_status, &status);
			cmds = cmds->next;
		}
		free_cmds(cmds_first);
	}
	return (0);
}
