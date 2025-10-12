/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 21:07:16 by cyang             #+#    #+#             */
/*   Updated: 2025/10/11 19:36:18 by cyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->key, current->value);
		else
			printf("%s\n", current->key);
		current = current->next;
	}
}
