/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:22:51 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/17 04:03:49 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin_fn(char *fn_name)
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

static int	exec_fn(t_cmd *cmds, t_data *data)
{
	int	result;

	result = 0;
	if (!ft_strcmp(cmds->args[0], "echo"))
		result = ft_echo(cmds->args);
	else if (!ft_strcmp(cmds->args[0], "pwd"))
		result = ft_pwd();
	else if (!ft_strcmp(cmds->args[0], "cd"))
		result = ft_cd(cmds->args[1], &data->env_list);
	else if (!ft_strcmp(cmds->args[0], "env"))
		result = ft_env(cmds->args, data->env_list);
	else if (!ft_strcmp(cmds->args[0], "export"))
		result = ft_export(cmds->args, &data->env_list);
	else if (!ft_strcmp(cmds->args[0], "exit"))
	{
		ft_exit(cmds, data);
		result = data->exit_status;
	}
	else if (!ft_strcmp(cmds->args[0], "unset"))
		result = ft_unset(cmds->args, &data->env_list);
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
	result = exec_fn(cmds, data);
	if (cmds->redirs)
	{
		dup2(fds.read_fd, STDIN_FILENO);
		dup2(fds.write_fd, STDOUT_FILENO);
		close(fds.read_fd);
		close(fds.write_fd);
	}
	return (result);
}
