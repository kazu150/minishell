/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 20:59:29 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/02 18:38:58 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setenv(char *target, char *value, t_env **env_list)
{
	t_env	*current;
	char	*free_target;

	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->key, target) == 0)
		{
			free_target = current->value;
			current->value = value;
			free(free_target);
			return ;
		}
		current = current->next;
	}
	error_exit("ft_setenv");
}

int	ft_cd(char *path, t_env **env_list)
{
	char	*target_path;
	char	*old_pwd;
	int		res;
	char	*pwd;
	char	*home;

	old_pwd = getcwd(NULL, 0);
	home = ft_getenv(*env_list, "HOME");
	if (path == NULL)
		target_path = home;
	else
		target_path = path;
	res = chdir(target_path);
	if (res < 0)
		return (perror(ft_strjoin("cd: ", target_path)), 1);
	pwd = getcwd(NULL, 0);
	ft_setenv("OLDPWD", old_pwd, env_list);
	ft_setenv("PWD", pwd, env_list);
	return (0);
}
