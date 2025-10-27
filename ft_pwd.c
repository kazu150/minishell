/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 19:38:46 by cyang             #+#    #+#             */
/*   Updated: 2025/10/27 09:34:54 by cyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **args)
{
	char	*cwd;
	cwd = getcwd(NULL, 0);

	(void)args;
	// if (args && args[1] != NULL)
	// {
	// 	ft_putendl_fd("pwd: too many arguments", 2);
	// 	return (1);
	// }
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}