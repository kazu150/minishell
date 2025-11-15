/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:53:34 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/15 11:08:50 by kaisogai         ###   ########.fr       */
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

void	free_cmds(t_cmd *cmds)
{
	if (cmds == NULL)
		return ;
	free_all(cmds->args);
	free(cmds->redirs);
	free(cmds);
}

void	free_key_value(char *key, char *value)
{
	free(key);
	free(value);
}
