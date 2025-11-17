/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:22:51 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/17 01:17:35 by codespace        ###   ########.fr       */
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

int	exec_fn(t_cmd *cmds, t_env **env_list)
{
	int	result;

	if (!ft_strcmp(cmds->args[0], "echo"))
		result = ft_echo(cmds->args);
	if (!ft_strcmp(cmds->args[0], "pwd"))
		result = ft_pwd();
	if (!ft_strcmp(cmds->args[0], "cd"))
		result = ft_cd(cmds->args[1], env_list);
	if (!ft_strcmp(cmds->args[0], "env"))
		result = ft_env(cmds->args, *env_list);
	if (!ft_strcmp(cmds->args[0], "export"))
		result = ft_export(cmds->args, env_list);
	if (!ft_strcmp(cmds->args[0], "exit"))
		ft_exit(cmds, env_list);
	if (!ft_strcmp(cmds->args[0], "unset"))
		result = ft_unset(cmds->args, env_list);
	return (result);
}

int	exec_builtin_fn(t_cmd *cmds, t_data *data)
{
	t_fds	fds;
	int		result;

	expand_args(cmds->args, data);
	if (!is_builtin_fn(cmds->args[0]))
		return (-1);
	if (cmds->redirs)
		fds = expand_redirs(cmds->redirs, data);
	result = exec_fn(cmds, &data->env_list);
	if (cmds->redirs)
	{
		dup2(fds.read_fd, STDIN_FILENO);
		dup2(fds.write_fd, STDOUT_FILENO);
		close(fds.read_fd);
		close(fds.write_fd);
	}
	return (result);
}
