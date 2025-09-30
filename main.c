/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:32:14 by kaisogai          #+#    #+#             */
/*   Updated: 2025/09/29 17:28:52 by cyang            ###   ########.fr       */
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

int	execute(char **args, t_redir *redirs, char **envp)
{
	char		*cmd;
	extern char	**environ;
	int			fd;
	char		*target;

	while (redirs)
	{
		if (redirs->type == R_IN || redirs->type == R_HDOC)
		{
			target = expand(redirs->target);
			if (redirs->type == R_IN)
				fd = open(target, O_RDONLY);
			else if (redirs->type == R_HDOC)
				fd = setup_heredoc(redirs->target);
			if (fd == -1)
				(free_split(args), error_exit(target));
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redirs->type == R_OUT || redirs->type == R_APP)
		{
			if (redirs->type == R_OUT)
				fd = open(expand(redirs->target), O_WRONLY | O_CREAT | O_TRUNC,
						0644);
			else if (redirs->type == R_APP)
				fd = open(expand(redirs->target), O_WRONLY | O_CREAT | O_APPEND,
						0644);
			if (fd == -1)
				(free_split(args), error_exit(target));
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redirs = redirs->next;
	}
	args = expand_all(args);
	if (!args)
		error_exit(MALLOC);
	if (args[0] == NULL)
		handle_command_path_error(args, 1, 0);
	// build-in commands
	if (!ft_strcmp(args[0], "echo"))
	{
		ft_echo(args);
		exit(0);
	}
	cmd = build_command_path(args, envp);
	if (execve(cmd, args, environ) == -1)
		(free(args), execve_error_exit(cmd));
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

// gcc main.c -lreadline -o main
int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	char	*line;
	int		status;
	t_cmd	*cmds;

	(void)argc;
	(void)argv;
	line = NULL;
	while (1)
	{
		line = readline("> ");
		add_history(line);
		if (line == NULL || strlen(line) == 0)
		{
			free(line);
			break ;
		}
		pid = fork();
		if (pid == -1)
			error_exit(FORK);
		cmds = parse_input(line);
		// TODO
		// - PIPEで次のコマンドに実行結果を渡す(nextがあったら)
		while (cmds)
		{
			if (pid == 0)
				return (execute(cmds->args, cmds->redirs, envp));
			else
			{
				waitpid(pid, &status, 0);
				free(line);
			}
			cmds = cmds->next;
		}
	}
	printf("exit\n");
	return (0);
}
