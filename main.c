#include "pipex.h"

void	error_exit(char *error_target)
{
	perror(error_target);
	exit(EXIT_FAILURE);
}

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

int	execute(char *str, char **envp)
{
	char		*cmd;
	extern char	**environ;
	char		**args;

	args = ft_split(str, ' ');
	if (!args)
		error_exit(MALLOC);
	if (args[0] == NULL)
		handle_command_path_error(args, 1, 0);
	cmd = build_command_path(args, envp);
	if (execve(cmd, args, environ) == -1)
		(free(args), execve_error_exit(cmd));
	return (0);
}
// gcc main.c -lreadline -o main
int	main(int argc, char **argv, char **envp)
{
	pid_t pid;
	(void)argc;
	(void)argv;
	char *line = NULL;
	int status;

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
		if (pid == 0)
			return (execute(line, envp));
		else
		{
			waitpid(pid, &status, 0);
			free(line);
		}
	}
	printf("exit\n");
	return (0);
}