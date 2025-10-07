/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:32:14 by kaisogai          #+#    #+#             */
/*   Updated: 2025/10/07 18:59:44 by kaisogai         ###   ########.fr       */
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

int	execute(char **args, char **envp)
{
	char		*cmd;
	extern char	**environ;

	// int			fd;
	// char		*target;
	// while (redirs)
	// {
	// 	if (redirs->type == R_IN || redirs->type == R_HDOC)
	// 	{
	// 		target = expand(redirs->target);
	// 		if (redirs->type == R_IN)
	// 			fd = open(target, O_RDONLY);
	// 		else if (redirs->type == R_HDOC)
	// 			fd = setup_heredoc(redirs->target);
	// 		if (fd == -1)
	// 			(free_split(args), error_exit(target));
	// 		dup2(fd, STDIN_FILENO);
	// 		close(fd);
	// 	}
	// 	else if (redirs->type == R_OUT || redirs->type == R_APP)
	// 	{
	// 		if (redirs->type == R_OUT)
	// 			fd = open(expand(redirs->target), O_WRONLY | O_CREAT | O_TRUNC,
	// 					0644);
	// 		else if (redirs->type == R_APP)
	// 			fd = open(expand(redirs->target), O_WRONLY | O_CREAT | O_APPEND,
	// 					0644);
	// 		if (fd == -1)
	// 			(free_split(args), error_exit(target));
	// 		dup2(fd, STDOUT_FILENO);
	// 		close(fd);
	// 	}
	// 	redirs = redirs->next;
	// }
	// args = expand_all(args);
	// if (!args)
	// 	error_exit(MALLOC);
	if (args[0] == NULL)
		handle_command_path_error(args, 1, 0);
	// // build-in commands
	// if (!ft_strcmp(args[0], "echo"))
	// {
	// 	ft_echo(args);
	// 	exit(0);
	// }
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
// ctrl C　の時
void	sigIntHandler(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();       //　readlineに改行を伝える
	rl_replace_line("", 0); //　USERが入力したバッファーをクリーン
	rl_redisplay();         //　promptを表示しなおす
}

// void	sigQuitHandler(int signo)
// {
// 	// シグナル番号とシグナルの説明を表示
// 	printf("sigquit %d", signo);
// 	fflush(stdout); // 標準出力のバッファを即時反映
// }

int	handle_parent_builtin(char **args)
{
	if (!args)
		return (0);
	if (!ft_strcmp(args[0], "cd"))
	{
		ft_cd(args[1]);
		return (1);
	}
	return (0);
}

// gcc main.c -lreadline -o main
int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		status;
	char	*line;
	t_cmd	*cmds;

	(void)argc;
	(void)argv;
	line = NULL;
	signal(SIGINT, sigIntHandler);
	signal(SIGQUIT, SIG_IGN); // SIG_IGNはhandlerのコンスト。意味：Ignore Signal
	while (1)
	{
		line = readline("> ");
		if (line == NULL) // Ctrl + D
		{
			free(line);
			break ;
		}
		if (ft_strlen(line) == 0)
		{
			free(line);
			continue ;
		}
		add_history(line);
		cmds = parse_input(line);
		expand(cmds->args, cmds->redirs);
		if (!ft_strcmp(cmds->args[0], "echo"))
		{
			ft_echo(cmds->args);
			continue ;
		}
		if (!ft_strcmp(cmds->args[0], "pwd"))
		{
			ft_pwd();
			continue ;
		}
		if (!ft_strcmp(cmds->args[0], "cd"))
		{
			ft_cd(cmds->args[1]);
			continue ;
		}
		pid = fork();
		if (pid == -1)
			error_exit(FORK);
		// TODO
		// - PIPEで次のコマンドに実行結果を渡す(nextがあったら)
		while (cmds)
		{
			if (pid == 0)
			{
				// signal(SIGINT, SIG_DFL);
				// signal(SIGQUIT, SIG_DFL);
				return (execute(cmds->args, envp));
			}
			else
			{
				waitpid(pid, &status, 0);
				free(line);
			}
			cmds = cmds->next;
		}
	}
	return (0);
}
