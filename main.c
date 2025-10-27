/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:32:14 by kaisogai          #+#    #+#             */
/*   Updated: 2025/10/27 15:32:45 by kaisogai         ###   ########.fr       */
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
// ctrl C　の時
void	sigIntHandler(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();       //　readlineに改行を伝える
	rl_replace_line("", 0); //　USERが入力したバッファーをクリーン
	rl_redisplay();         //　promptを表示しなおす
}

int	without_fork(char *line, t_cmd *cmds, t_env **env_list, int exit_status, char **envp)
{
	int		builtin_status;

	expand_args(cmds->args, *env_list, exit_status);
	builtin_status = exec_builtin_fn(cmds, env_list, exit_status);
	if (builtin_status != -1)
	{
		exit_status = builtin_status;
		free(line);
		return (0);
	}
	return (execute(cmds->args, envp));
}

// gcc main.c -lreadline -o main
int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		status;
	char	*line;
	t_cmd	*cmds;
	t_env	*env_list;
	int		exit_status;
	int		builtin_status;

	(void)argc;
	(void)argv;
	exit_status = 0;
	line = NULL;
	signal(SIGINT, sigIntHandler);
	signal(SIGQUIT, SIG_IGN); // SIG_IGNはhandlerのコンスト。意味：Ignore Signal
	env_list = init_env(envp);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			free_exit(line);
		if (ft_strlen(line) == 0)
		{
			free(line);
			continue ;
		}
		add_history(line);
		cmds = parse_input(line);
		if (!cmds->next)
		{
			without_fork(line, cmds, &env_list, exit_status, envp);
			continue ;
		}
		cmds = parse_input(line);
		expand_args(cmds->args, env_list, exit_status);
		if (cmds->next)
			pid = fork();
		builtin_status = exec_builtin_fn(cmds, &env_list, exit_status);
		if (builtin_status != -1)
		{
			exit_status = builtin_status;
			free(line);
			continue ;
		}
		if (pid == -1)
			error_exit(FORK);
		// TODO
		// - PIPEで次のコマンドに実行結果を渡す(nextがあったら)
		while (cmds)
		{
			if (pid == 0)
			{
				expand_redirs(cmds->redirs, env_list, exit_status);
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
