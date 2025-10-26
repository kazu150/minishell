/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 20:59:29 by kaisogai          #+#    #+#             */
/*   Updated: 2025/10/19 15:56:13 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

void	ft_setenv(char *target, char *value)
{
	int		i;
	char	**current_arg;
	char	*new_arg;
	int		key_len;
	int		value_len;

	i = 0;
	while (environ[i])
	{
		current_arg = ft_split(environ[i], '=');
		if (ft_strcmp(current_arg[0], target) == 0)
		{
			key_len = ft_strlen(current_arg[0]);
			value_len = ft_strlen(value);
			new_arg = malloc(sizeof(char) * (key_len + value_len + 2));
			ft_bzero(new_arg, key_len + value_len + 2);
			ft_strlcat(new_arg, current_arg[0], key_len + value_len + 2);
			new_arg[key_len] = '=';
			ft_strlcat(&(new_arg[key_len + 1]), value, key_len + value_len + 2);
			environ[i] = new_arg;
			return ;
		}
		i++;
	}
	error_exit("ft_setenv");
}

int 	ft_cd(char *path)
{
	char	*old_pwd;
	int		res;
	char	*pwd;

	old_pwd = getcwd(NULL, 0);
	res = chdir(path);
	if (res < 0)
		return (perror(ft_strjoin("cd: ", path)), 1);
	pwd = getcwd(NULL, 0);
	ft_setenv("OLDPWD", old_pwd);
	ft_setenv("PWD", pwd);
	return 0;
}
