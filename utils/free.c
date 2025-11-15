/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:53:34 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/15 15:11:53 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_cmds(t_cmd **cmds)
{
	t_cmd	*target;
	t_cmd	*current;

	target = *cmds;
	while (target)
	{
		current = target->next;
		free_all(target->args);
		free(target->redirs);
		free(target);
		target = current;
	}
	*cmds = NULL;
}

void	free_key_value(char *key, char *value)
{
	free(key);
	free(value);
}
