/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 19:12:11 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/01 21:43:53 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_command_path_error(t_cmd *cmds, int has_permission_error,
		char **paths)
{
	char	*str;
	int		len;

	if (cmds->args[0] == NULL)
		str = ft_strjoin("", ": Permission denied\n");
	else if (has_permission_error)
		str = ft_strjoin(cmds->args[0], ": Permission denied\n");
	else
		str = ft_strjoin(cmds->args[0], ": command not found\n");
	if (!str)
		error_exit(MALLOC);
	len = ft_strlen(str);
	write(2, str, len);
	if (paths)
		free_split(paths);
	free(str);
	if (cmds)
	{
		free_all(cmds->args);
		free(cmds->redirs);
		free(cmds);
	}
	if (has_permission_error)
		exit(126);
	else
		exit(127);
}

char	**get_default_paths(t_env **env_list)
{
	char	**paths;
	t_env *list;

	paths = NULL;
	list = *env_list;
	while (list)
	{
		if (!ft_strcmp(list->key, "PATH"))
		{
			paths = ft_split(list->value, ':');
			if (!paths)
				error_exit(MALLOC);
			return (paths);
		}
		list = list->next;
	}
	return (NULL);
}

char	*pathjoin(const char *path1, const char *path2)
{
	char	*with_slash;
	char	*full_path;

	with_slash = ft_strjoin(path1, "/");
	if (!with_slash)
		error_exit(MALLOC);
	full_path = ft_strjoin(with_slash, path2);
	if (!full_path)
		error_exit(MALLOC);
	free(with_slash);
	return (full_path);
}

char	*build_command_path(t_cmd *cmds, t_env **env_list)
{
	char	*command_path;
	int		i;
	char	**paths;
	int		has_permission_error;

	if (cmds->args[0][0] == '/' || cmds->args[0][0] == '.')
		return (cmds->args[0]);
	has_permission_error = 0;
	paths = get_default_paths(env_list);
	i = 0;
	command_path = NULL;
	while (paths && paths[i])
	{
		command_path = pathjoin(paths[i++], cmds->args[0]);
		if (!command_path)
			error_exit(MALLOC);
		if (access(command_path, X_OK) == 0)
			break ;
		if (errno == EACCES)
			has_permission_error = 1;
		free(command_path);
	}
	if (!paths || !paths[i] || !command_path)
		handle_command_path_error(cmds, has_permission_error, paths);
	return (command_path);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] - s2[i] != 0)
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
