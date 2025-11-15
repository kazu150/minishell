/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:15:12 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/15 14:54:30 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_exit(t_cmd *cmds, t_env **env_list)
{
	if (cmds)
	{
		free_cmds(&cmds);
	}
	free_env_list(env_list);
	free_exit(NULL);
	return (1);
}
