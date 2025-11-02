/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:15:12 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/02 12:35:04 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_list(t_env **env_list)
{
	t_env *target;

	target = *env_list;
	while (target)
	{
		free(target->key);
		free(target->value);
		target = target->next;
	}
	free(env_list);
}

int	ft_exit(t_cmd *cmds, char *line, t_env **env_list)
{
	if (cmds)
	{
		free_all(cmds->args);
		free(cmds->redirs);
		free(cmds);
	}
	free_env_list(env_list);
	free_exit(line);
	return (1);
}
