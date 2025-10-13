/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 15:13:01 by kaisogai          #+#    #+#             */
/*   Updated: 2025/10/13 14:46:30 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

void	ft_unset(char *arg)
{
	int		i;
	char	**current_arg;

	if (arg == NULL)
		message_exit("unset: not enough arguments", EXIT_FAILURE);
	i = 0;
	while (environ[i])
	{
		current_arg = ft_split(environ[i], '=');
		if (ft_strcmp(current_arg[0], arg) == 0)
		{
			while (environ[i])
			{
				environ[i] = environ[i + 1];
				i++;
			}
			environ[i] = 0;
			return ;
		}
		i++;
	}
}
