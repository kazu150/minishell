/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:32:14 by kaisogai          #+#    #+#             */
/*   Updated: 2025/09/26 22:25:55 by cyang            ###   ########.fr       */
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

static char	*store_before_dollor(char *result, char *str, int dollar_pos)
{
	char	*tmp;
	char	*new_result;

	if (dollar_pos > 0)
	{
		tmp = ft_substr(str, 0, dollar_pos);
		new_result = ft_strjoin(result, tmp);
		free(result);
		free(tmp);
		return (new_result);
	}
	return (result);
}

static char	*expand_and_add_var(char *result, char *str, int var_start, int var_end)
{
	char	*var_name;
	char	*var_value;
	char	*tmp;
	if (var_end > var_start)
	{
		var_name = ft_substr(str, var_start, var_end - var_start);
		var_value = getenv(var_name);
		if (var_value)
		{
			tmp = ft_strjoin(result, var_value);
			free(result);
			result = tmp;
		}
		free(var_name);
	}
	else
	{
		tmp = ft_strjoin(result, "$");
		free(result);
		result = tmp;
	}
	return (result);
}
static char	*add_after_var(char *result, char *str, int var_end)
{
	char	*rest;
	char	*tmp;

	if (str[var_end])
	{
		rest = ft_substr(str, var_end, ft_strlen(str) - var_end);
		tmp = ft_strjoin(result, rest);
		free(result);
		free(rest);
		return (tmp);
	}
	return (result);
}

char	*expand_with_var(char *str)
{
	char	*result;
	int		i;
	int		var_start;
	int		var_end;

	result = ft_strdup("");
	if (!result)
		error_exit(MALLOC);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			result = store_before_dollor(result, str, i);
			var_start = i + 1;
			var_end = var_start;
			while (str[var_end] && (ft_isalnum(str[var_end]) || str[var_end] == '_'))
				var_end++;
			result = expand_and_add_var(result, str, var_start, var_end);
			result = add_after_var(result, str, var_end);
			break;
		}
		i++;
	}
	free(str);
	return (result);
}

	// TODO
	// 例
	// "foo" → foo    
	// $FOO → bar
	// '$FOO' → $FOO  
	// "$FOO" → bar   
char	*expand(char *str)
{
	int		len;
	char	*transform;
	char	*without_quote;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	// "foo" → foo & '$FOO' → $FOO
	if ((str[0] == '\'' && str[len - 1] =='\'') || (str[0] == '\"' && str[len - 1] =='\"' && !ft_strchr(str,'$')))
	{
		transform = ft_substr(str, 1, len - 2);
		free(str);
		return (transform);
	}
	//"$FOO" → bar && $FOO → bar  home=3 skdjkf$home → skdjkf3
	if (str[0] == '\"' && str[len - 1] =='\"' && ft_strchr(str,'$'))
	{
		without_quote = ft_substr(str, 1, len - 2);
		free(str);
		transform = expand_with_var(without_quote);
		return (transform);
	}
	// "$FOO" → bar  
	else if (!ft_strchr(str, '\'') && !ft_strchr(str, '\"') && ft_strchr(str,'$'))
	{
		transform = expand_with_var(str);
		return (transform);
	}
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
