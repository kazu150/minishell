/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:32:14 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/17 03:34:08 by codespace        ###   ########.fr       */
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

t_cmd	*get_cmds_from_readline(t_data *data, t_cmd **cmds,
		t_cmd **cmds_first)
{
	char	*line;

	*cmds = NULL;
	*cmds_first = NULL;
	line = NULL;
	line = readline("minishell> ");
	if (line == NULL)
		ft_exit(NULL, data);
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
	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, SIG_IGN);
	data->env_list = init_env();
}

static void	readline_roop(t_pipe_fds *pipe_fds, t_data *data)
{
	t_cmd	*cmds;
	t_cmd	*cmds_first;

	while (1)
	{
		get_cmds_from_readline(data, &cmds, &cmds_first);
		if (cmds && cmds->args && !cmds->args[0])
		{
			if (cmds->redirs)
				handle_redirect_without_cmd(cmds, data);
			free_cmds(cmds);
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
	t_data		data;

	initialize(&pipe_fds, &data);
	readline_roop(&pipe_fds, &data);
	return (0);
}
