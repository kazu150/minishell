/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:18:32 by kaisogai          #+#    #+#             */
/*   Updated: 2025/09/23 13:38:23 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	output_child_process(char **argv, int pipe_in, char **envp)
{
	int			fd;
	char		*cmd;
	extern char	**environ;
	char		**args;
	char		*output_filename;

	args = tokenize(argv[3]);
	if (!args)
		error_exit(MALLOC);
	output_filename = argv[4];
	if (dup2(pipe_in, STDIN_FILENO) == -1)
		(free_split(args), error_exit(DUP2));
	close(pipe_in);
	fd = open(output_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		(free_split(args), error_exit(output_filename));
	if (args[0] == NULL)
		handle_command_path_error(args, 1, 0);
	cmd = build_command_path(args, envp);
	if (dup2(fd, STDOUT_FILENO) == -1)
		(free(cmd), free_split(args), error_exit(DUP2));
	close(fd);
	if (execve(cmd, args, environ) == -1)
		(free(args), execve_error_exit(cmd));
	return (0);
}

int	output(pid_t pid, char **argv, int d_pipe[2], char **envp)
{
	int		status;
	int		o_status;
	pid_t	o_pid;

	close(d_pipe[1]);
	o_pid = fork();
	if (o_pid < 0)
		error_exit(FORK);
	if (o_pid == 0)
		return (output_child_process(argv, d_pipe[0], envp));
	else
	{
		if (waitpid(pid, &status, 0) < 0 || waitpid(o_pid, &o_status, 0) < 0)
			error_exit(WAITPID);
		if (WIFEXITED(status) && WIFEXITED(o_status))
		{
			close(d_pipe[0]);
			return (WEXITSTATUS(o_status));
		}
	}
	exit(0);
}
