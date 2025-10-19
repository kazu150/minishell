/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:32:14 by kaisogai          #+#    #+#             */
/*   Updated: 2025/10/16 18:08:25 by kaisogai         ###   ########.fr       */
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

int	is_builtin_fn(char **args, t_redir *redirs, t_env *env_list)
{
	if (!ft_strcmp(args[0], "echo"))
		return (expand_redirs(redirs, env_list), ft_echo(args), 1);
	if (!ft_strcmp(args[0], "pwd"))
		return (expand_redirs(redirs, env_list), ft_pwd(), 1);
	if (!ft_strcmp(args[0], "cd"))
		return (expand_redirs(redirs, env_list), ft_cd(args[1]), 1);
	if (!ft_strcmp(args[0], "env"))
		return (expand_redirs(redirs, env_list), ft_env(env_list), 1);
	if (!ft_strcmp(args[0], "export"))
		return (expand_redirs(redirs, env_list), ft_export(args, &env_list), 1);
	if (!ft_strcmp(args[0], "exit"))
		return (expand_redirs(redirs, env_list), ft_exit(), 1);
	return (0);
}

// gcc main.c -lreadline -o main
int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		status;
	char	*line;
	t_cmd	*cmds;
	t_env	*env_list;

	(void)argc;
	(void)argv;
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
		expand_args(cmds->args, env_list);
		if (is_builtin_fn(cmds->args, cmds->redirs, env_list))
			continue ;
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
		if (!ft_strcmp(cmds->args[0], "unset"))
		{
			ft_unset(cmds->args[1], &env_list);
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
				expand_redirs(cmds->redirs, env_list);
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
