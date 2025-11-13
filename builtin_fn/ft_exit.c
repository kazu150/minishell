/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:15:12 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/13 14:42:27 by codespace        ###   ########.fr       */
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

void	ft_exit(t_cmd *cmds, t_env **env_list)
{
	if (cmds)
		free_cmds(cmds);
	if (env_list && *env_list)
		free_env_list(env_list);
	free_exit(NULL);
	rl_clear_history();
	exit(0);
}
