/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:32:14 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/09 14:28:29 by kaisogai         ###   ########.fr       */
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
	return (envp);
}

int	execute(t_cmd *cmds, t_env *env_list)
{
	char	*cmd;
	char	**envp;

	envp = env_list_to_envp(env_list);
	if (cmds->args[0] == NULL)
		handle_command_path_error(cmds, 1, 0);
	cmd = build_command_path(cmds, &env_list);
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

// gcc main.c -lreadline -o main
int	main(void)
{
	pid_t	pid;
	int		status;
	char	*line;
	t_cmd	*cmds;
	t_cmd	*cmds_first;
	t_env	*env_list;
	int		exit_status;
	int		builtin_status;

	exit_status = 0;
	line = NULL;
	signal(SIGINT, sigIntHandler);
	signal(SIGQUIT, SIG_IGN); // SIG_IGNはhandlerのコンスト。意味：Ignore Signal
	env_list = init_env();
	cmds = NULL;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			ft_exit(cmds, &env_list);
		if (ft_strlen(line) == 0)
		{
			free(line);
			continue ;
		}
		add_history(line);
		cmds = parse_input(line);
		cmds_first = cmds;
		free(line);
		if (!cmds)
			continue ;
		builtin_status = exec_builtin_fn(cmds, &env_list, exit_status);
		if (builtin_status != -1)
		{
			exit_status = builtin_status;
			free_cmds(cmds);
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
				expand_redirs(cmds->redirs, env_list, exit_status);
				return (execute(cmds, env_list));
			}
			else
			{
				waitpid(pid, &status, 0);
			}
			cmds = cmds->next;
		}
		if (cmds_first)
		{
			free_cmds(cmds_first);
		}
	}
	return (0);
}
