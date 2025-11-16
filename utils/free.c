/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:53:34 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/16 16:58:36 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static void	free_redirs(t_redir *redirs)
{
	t_redir	*current;

	while (redirs)
	{
		current = redirs->next;
		if (redirs->target)
			free(redirs->target);
		free(redirs);
		redirs = current;
	}
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*current;
	t_cmd	*next;

	if (cmds == NULL)
		return ;
	current = cmds;
	while (current)
	{
		next = current->next;
		if (current->args)
			free_all(current->args);
		free_redirs(current->redirs);
		free(current);
		current = next;
	}
}

void	free_key_value(char *key, char *value)
{
	free(key);
	free(value);
}
