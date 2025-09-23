/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:18:46 by kaisogai          #+#    #+#             */
/*   Updated: 2025/09/23 13:38:07 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_child_process(char **argv, int d_pipe[2], char **envp)
{
	int			fd;
	char		*cmd;
	extern char	**environ;
	char		**args;

	args = tokenize(argv[2]);
	if (!args)
		error_exit(MALLOC);
	close(d_pipe[0]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		(free_split(args), error_exit(argv[1]));
	if (args[0] == NULL)
		handle_command_path_error(args, 1, 0);
	cmd = build_command_path(args, envp);
	if (dup2(fd, STDIN_FILENO) == -1)
		(free(cmd), free_split(args), error_exit(DUP2));
	close(fd);
	if (dup2(d_pipe[1], STDOUT_FILENO) == -1)
		(free(cmd), free_split(args), error_exit(DUP2));
	close(d_pipe[1]);
	if (execve(cmd, args, environ) == -1)
		(free(args), execve_error_exit(cmd));
	return (0);
}
