/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 20:59:29 by kaisogai          #+#    #+#             */
/*   Updated: 2025/10/07 19:09:22 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char *path)
{
	char	*old_pwd;
	int		res;
	char	*pwd;

	old_pwd = getcwd(NULL, 0);
	res = chdir(path);
	if (res < 0)
		perror(ft_strjoin("cd: ", path));
	pwd = getcwd(NULL, 0);
	ft_setenv("OLDPWD", old_pwd);
	ft_setenv("PWD", pwd);
}
