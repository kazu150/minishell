/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:32:14 by kaisogai          #+#    #+#             */
/*   Updated: 2025/09/14 16:32:15 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	is_redir(char *arg)
{
	if (ft_strncmp(arg, R_IN, 2) == 0)
		return (1);
	if (ft_strncmp(arg, R_OUT, 2) == 0)
		return (1);
	if (ft_strncmp(arg, R_APP, 3) == 0)
		return (1);
	if (ft_strncmp(arg, R_HDOC, 3) == 0)
		return (1);
	return (0);
}

// input: cat input.txt | grep hello > out.txt
t_cmd	*parse_input(char *input)
{
	char	**words;
	int		i;
	t_cmd	*cmd;

	words = ft_split(input, ' ');
	i = 0;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		exit(MALLOC);
	cmd->args = NULL;
	cmd->next = NULL;
	cmd->redirs = NULL;
	while (words)
	{
		if (is_redir(words[i]))
		{
			// words[i]がREDIRなら、現在のnodeのredirsに追加
			if (!cmd->redirs)
				cmd->redirs = malloc(sizeof(t_redir));
			cmd->redirs->type = words[i];
			cmd->redirs->target = words[i + 1];
			cmd->redirs->next = NULL;
		}
		else if (ft_strncmp(words[i], "|", 2) == 0)
		{
			// words[i]がPIPEなら、次のnodeを作成
			cmd->next = malloc(sizeof(t_cmd));
			if (!cmd)
				exit(MALLOC);
			cmd->args = NULL;
			cmd->next = NULL;
			cmd->redirs = NULL;
		}
		else
		{
			// words[i]が上記以外なら、現在のnodeのargsに追加
			if (!cmd->args)
				cmd->args = malloc(sizeof(char **));
			cmd->args = words[i];
			cmd->args++;
		}
		i++;
	}
}

// gcc main.c -lreadline -o main
int	main(int argc, char **argv, char **envp)
{
	pid_t pid;
	(void)argc;
	(void)argv;
	char *line = NULL;
	int status;
	t_cmd *cmds;

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
		// TODO: 入力文字列の解析（parsing）
		cmds = perse_input(line);
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