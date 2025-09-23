/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:32:14 by kaisogai          #+#    #+#             */
/*   Updated: 2025/09/23 17:19:08 by kaisogai         ###   ########.fr       */
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

char	*expand(char *str)
{
	// TODO
	return (str);
}

char	**expand_all(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		strs[i] = expand(strs[i]);
		i++;
	}
	return (strs);
}

int	execute(char **args, t_redir *redirs, char **envp)
{
	char		*cmd;
	extern char	**environ;
	int			fd;

	// redirs対応
	while (redirs)
	{
		if (redirs->type == R_IN)
		{
			fd = open(expand(redirs->target), O_RDONLY);
			// TODO: free something
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redirs->type == R_OUT)
		{
			fd = open(expand(redirs->target), O_WRONLY | O_CREAT | O_TRUNC,
					0644);
			// TODO: free something
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
