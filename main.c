/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:32:14 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/15 15:38:28 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*get_cmds_from_readline(t_env **env_list, t_cmd **cmds,
		t_cmd **cmds_first)
{
	char	*line;

	*cmds = NULL;
	*cmds_first = NULL;
	line = NULL;
	line = readline("> ");
	if (line == NULL)
		ft_exit(*cmds, env_list);
	if (ft_strlen(line) == 0)
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

void	initialize(t_pipe_fds *pipe_fds, int *exit_status,
		t_env **env_list)
{
	pipe_fds->pipe_fd[0] = -1;
	pipe_fds->pipe_fd[1] = -1;
	pipe_fds->prev_read_fd = -1;
	*exit_status = 0;
	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, SIG_IGN);
	*env_list = init_env();
}

void	readline_roop(t_pipe_fds *pipe_fds, int *exit_status,
		t_env **env_list)
{
	t_cmd	*cmds;
	t_cmd	*cmds_first;

	while (1)
	{
		get_cmds_from_readline(env_list, &cmds, &cmds_first);
		while (cmds)
		{
			if (cmds->next)
				run_normal_command(cmds, pipe_fds, env_list,
					exit_status);
			else
				run_last_command(cmds, pipe_fds, env_list,
					exit_status);
			cmds = cmds->next;
		}
		free_cmds(&cmds_first);
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
