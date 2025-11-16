/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 12:51:38 by codespace         #+#    #+#             */
/*   Updated: 2025/11/16 14:49:45 by cyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_export_error(char *invalid_key)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(invalid_key, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (1);
}

int	is_valid_export_key(const char *key)
{
	int	i;

	if (!key || !key[0])
		return (0);
	if (!(ft_isalpha((unsigned char)key[0]) || key[0] == '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!(ft_isalnum((unsigned char)key[i]) || key[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
