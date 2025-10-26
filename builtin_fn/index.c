/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:22:51 by kaisogai          #+#    #+#             */
/*   Updated: 2025/10/26 17:33:21 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin_fn(char *fn_name)
{
	if (!ft_strcmp(fn_name, "echo"))
		return (1);
	if (!ft_strcmp(fn_name, "pwd"))
		return (1);
	if (!ft_strcmp(fn_name, "cd"))
		return (1);
	if (!ft_strcmp(fn_name, "env"))
		return (1);
	if (!ft_strcmp(fn_name, "export"))
		return (1);
	if (!ft_strcmp(fn_name, "exit"))
		return (1);
	if (!ft_strcmp(fn_name, "unset"))
		return (1);
	return (0);
}

int	exec_builtin_fn(t_cmd *cmds, t_env **env_list, int exit_status)
{
	t_fds	fds;

	if (!is_builtin_fn(cmds->args[0]))
		return (0);
	fds = expand_redirs(cmds->redirs, *env_list, exit_status);
	if (!ft_strcmp(cmds->args[0], "echo"))
		ft_echo(cmds->args);
	if (!ft_strcmp(cmds->args[0], "pwd"))
		ft_pwd(cmds->args);
	if (!ft_strcmp(cmds->args[0], "cd"))
		ft_cd(cmds->args[1]);
	if (!ft_strcmp(cmds->args[0], "env"))
		ft_env(cmds->args, *env_list);
	if (!ft_strcmp(cmds->args[0], "export"))
		ft_export(cmds->args, env_list);
	if (!ft_strcmp(cmds->args[0], "exit"))
		ft_exit();
	if (!ft_strcmp(cmds->args[0], "unset"))
		ft_unset(cmds->args[1], env_list);
	dup2(fds.read_fd, STDIN_FILENO);
	dup2(fds.write_fd, STDOUT_FILENO);
	return (0);
}
