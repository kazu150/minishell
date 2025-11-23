/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 16:03:44 by cyang             #+#    #+#             */
/*   Updated: 2025/11/22 16:04:22 by cyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_cmd *cmds, t_env *env_list)
{
	char	*cmd;
	char	**envp;

	if (!cmds->args || cmds->args[0] == NULL)
	{
		if (cmds->redirs)
			exit(0);
		else
			handle_command_path_error(cmds, 1, 0);
	}
	cmd = build_command_path(cmds, &env_list, 0, 0);
	envp = build_envp_with_assigns(env_list, cmds->assigns);
	if (execve(cmd, cmds->args, envp) == -1)
	{
		free_all(envp);
		execve_error_exit(cmd);
	}
	return (0);
}
