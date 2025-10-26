/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:59:02 by cyang             #+#    #+#             */
/*   Updated: 2025/10/26 13:53:57 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (args[1] != NULL && !ft_strcmp(args[1], "-n"))
	{
		i = 2;
		newline = 0;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (newline == 1)
		printf("\n");
	return (0);
}
