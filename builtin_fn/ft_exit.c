/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:15:12 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/22 07:41:36 by kaisogai         ###   ########.fr       */
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
		i++;
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

static void	cleanup_and_exit(t_cmd **cmds, t_env **env_list,
		long long exit_code)
{
	if (cmds)
		free_cmds(cmds);
	if (env_list && *env_list)
		free_env_list(env_list);
	if (exit_code > 255)
		exit_code = 255;
	free_exit(NULL, exit_code);
}

int	fits_in_ll(char *s)
{
	int		neg;
	char	*limit;
	int		len_s;
	int		len_l;

	neg = 0;
	if (*s == '-')
	{
		neg = 1;
		s++;
	}
	if (neg)
		limit = "9223372036854775808";
	else
		limit = "9223372036854775807";
	len_s = ft_strlen(s);
	len_l = ft_strlen(limit);
	if (len_s < len_l)
		return (1);
	if (len_s > len_l)
		return (0);
	if (ft_strcmp(s, limit) <= 0)
		return (1);
	return (0);
}

void	ft_exit(t_cmd **cmds, t_data *data)
{
	char	*exit_code;

	if (cmds && *cmds)
		printf("exit\n");
	if (!*cmds || !(*cmds)->args || !(*cmds)->args[0] || !(*cmds)->args[1])
	{
		cleanup_and_exit(cmds, &data->env_list, data->exit_status);
	}
	exit_code = (*cmds)->args[1];
	if ((*cmds)->args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		data->exit_status = 1;
		return ;
	}
	if (!is_numeric(exit_code) || !fits_in_ll(exit_code))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(exit_code, 2);
		ft_putendl_fd(": numeric argument required", 2);
		cleanup_and_exit(cmds, &data->env_list, 2);
	}
	cleanup_and_exit(cmds, &data->env_list, ft_atoll(exit_code));
}
