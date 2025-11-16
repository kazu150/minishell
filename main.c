/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:32:14 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/16 14:18:53 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_all_space(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

t_cmd	*get_cmds_from_readline(t_env **env_list, t_cmd **cmds,
		t_cmd **cmds_first)
{
	char	*line;

	*cmds = NULL;
	*cmds_first = NULL;
	line = NULL;
	line = readline("minishell> ");
	if (line == NULL)
		ft_exit(*cmds, env_list);
	if (!ft_strlen(line) || is_all_space(line))
	{
		free(line);
		return (NULL);
	}
	add_history(line);
	*cmds = parse_input(line);
	*cmds_first = *cmds;
	free(line);
	return (*cmds);
}

static void	handle_redirect_without_cmd(t_cmd *cmds, t_env **env_list,
		int *exit_status)
{
	int	status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_exit(FORK);
	if (pid == 0)
	{
		expand_redirs(cmds->redirs, *env_list, *exit_status);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		*exit_status = status >> 8;
	}
}

void	initialize(t_pipe_fds *pipe_fds, int *exit_status, t_env **env_list)
{
	pipe_fds->pipe_fd[0] = -1;
	pipe_fds->pipe_fd[1] = -1;
	pipe_fds->prev_read_fd = -1;
	*exit_status = 0;
	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, SIG_IGN);
	*env_list = init_env();
}

void	readline_roop(t_pipe_fds *pipe_fds, int *exit_status, t_env **env_list)
{
	t_cmd	*cmds;
	t_cmd	*cmds_first;

	while (1)
	{
		get_cmds_from_readline(env_list, &cmds, &cmds_first);
		// 空コマンド　> < >> << + targetの対応
		if (cmds && cmds->args && !cmds->args[0])
		{
			if (cmds->redirs)
				handle_redirect_without_cmd(cmds, env_list, exit_status);
			free_cmds(cmds);
			continue ;
		}
		while (cmds)
		{
			if (cmds->next)
				run_normal_command(cmds, pipe_fds, env_list, exit_status);
			else
				run_last_command(cmds, pipe_fds, env_list, exit_status);
			cmds = cmds->next;
		}
		if (cmds_first)
		{
			free_cmds(cmds_first);
			cmds_first = NULL;
		}
	}
}

int	main(void)
{
	t_pipe_fds	pipe_fds;
	t_env		*env_list;
	int			exit_status;

	initialize(&pipe_fds, &exit_status, &env_list);
	readline_roop(&pipe_fds, &exit_status, &env_list);
	return (0);
}
