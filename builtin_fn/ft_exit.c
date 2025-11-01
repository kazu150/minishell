/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:15:12 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/01 18:52:48 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_cmd *cmds, char *line)
{
	if (cmds)
	{
		free_all(cmds->args);
		free(cmds->redirs);
		free(cmds);
	}
	free_exit(line);
	return (1);
}
