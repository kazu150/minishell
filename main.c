/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:32:14 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/20 13:12:48 by cyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*get_cmds_from_readline(t_data *data, t_cmd **cmds,
		t_cmd **cmds_first)
{
	char	*line;

	*cmds = NULL;
	*cmds_first = NULL;
	line = NULL;
	line = readline("minishell> ");
	if (line == NULL)
		ft_exit(cmds, data);
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

static void	handle_redirect_without_cmd(t_cmd *cmds, t_data *data)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_exit(FORK);
	if (pid == 0)
	{
		set_default_signals();
		g_sigint_received = 0;
		expand_redirs(cmds->redirs, data);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		data->exit_status = status >> 8;
	}
}

static void	initialize(t_pipe_fds *pipe_fds, t_data *data)
{
	pipe_fds->pipe_fd[0] = -1;
	pipe_fds->pipe_fd[1] = -1;
	pipe_fds->prev_read_fd = -1;
	data->exit_status = 0;
	set_parent_signals();
	data->env_list = init_env();
}

static void	readline_roop(t_pipe_fds *pipe_fds, t_data *data)
{
	t_cmd	*cmds;
	t_cmd	*cmds_first;

	while (1)
	{
		get_cmds_from_readline(data, &cmds, &cmds_first);
		if (g_sigint_received)
		{
			g_sigint_received = 0;
			if (cmds_first)
				free_cmds(&cmds_first);
			continue;
		}
		if (cmds && cmds->args && !cmds->args[0])
		{
			if (cmds->redirs)
				handle_redirect_without_cmd(cmds, data);
			free_cmds(&cmds);
			continue ;
		}
		while (cmds)
		{
			if (cmds->next)
				run_normal_command(cmds, pipe_fds, data);
			else
				run_last_command(cmds, pipe_fds, data);
			cmds = cmds->next;
		}
		free_cmds(&cmds_first);
	}
}

int	main(void)
{
	t_pipe_fds	pipe_fds;
	t_data		data;

	initialize(&pipe_fds, &data);
	readline_roop(&pipe_fds, &data);
	return (0);
}
