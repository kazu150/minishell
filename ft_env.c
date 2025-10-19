/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 21:07:16 by cyang             #+#    #+#             */
/*   Updated: 2025/10/19 11:42:07 by cyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **args, t_env *env_list)
{
	t_env	*current;

	current = env_list;
	if (args && args[1] != NULL)
	{
		ft_putendl_fd("env: "" No such file or directory", 2);
		return (127);
	}
	while (current)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}
