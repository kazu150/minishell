/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:15:12 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/22 14:53:33 by cyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(const char *s)
{
	int	i;

	i = 0;
	if (!s || !*s)
		return (0);
	if (s[0] == '+' || s[0] == '-')
		i ++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	free_env_list(t_env **env_list)
{
	t_env	*target;
	t_env	*current;

	target = *env_list;
	while (target)
	{
		current = target->next;
		free(target->key);
		free(target->value);
		free(target);
		target = current;
	}
	*env_list = NULL;
}

static void	cleanup_and_exit(t_cmd **cmds, t_env **env_list, int exit_code)
{
	if (cmds)
		free_cmds(cmds);
	if (env_list && *env_list)
		free_env_list(env_list);
	free_exit(NULL);
	rl_clear_history();
	exit(exit_code);
}

void	ft_exit(t_cmd **cmds, t_data *data)
{
	char	*arg;
	int		exit_code;

	// if (cmds && *cmds)
	printf("exit\n");
	if (!*cmds || !(*cmds)->args || !(*cmds)->args[0])
		cleanup_and_exit(cmds, &data->env_list, data->exit_status);
	if (!(*cmds)->args[1])
		cleanup_and_exit(cmds, &data->env_list, data->exit_status);
	arg = (*cmds)->args[1];
	if (!is_numeric(arg))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": numeric argument required", 2);
		cleanup_and_exit(cmds, &data->env_list, 2);
	}
	if ((*cmds)->args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		data->exit_status = 1;
		return ;
	}
	exit_code = ft_atoi(arg);
	cleanup_and_exit(cmds, &data->env_list, exit_code & 255);
}
