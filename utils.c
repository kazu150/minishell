/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 19:12:11 by kaisogai          #+#    #+#             */
/*   Updated: 2025/09/23 13:50:13 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_command_path_error(char **args, int has_permission_error,
		char **paths)
{
	char	*str;
	int		len;

	if (args[0] == NULL)
		str = ft_strjoin("", ": Permission denied\n");
	else if (has_permission_error)
		str = ft_strjoin(args[0], ": Permission denied\n");
	else
		str = ft_strjoin(args[0], ": command not found\n");
	if (!str)
		error_exit(MALLOC);
	len = ft_strlen(str);
	write(2, str, len);
	if (paths)
		free_split(paths);
	free(str);
	free_split(args);
	if (has_permission_error)
		exit(126);
	else
		exit(127);
}

char	**get_default_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	paths = NULL;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			envp[i] = envp[i] + 5;
			paths = ft_split(envp[i], ':');
			if (!paths)
				error_exit(MALLOC);
			return (paths);
		}
		i++;
	}
	return (paths);
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

char	*build_command_path(char **args, char **envp)
{
	char	*command_path;
	int		i;
	char	**paths;
	int		has_permission_error;

	if (args[0][0] == '/' || args[0][0] == '.')
		return (args[0]);
	has_permission_error = 0;
	paths = get_default_paths(envp);
	i = 0;
	command_path = NULL;
	while (paths && paths[i])
	{
		command_path = pathjoin(paths[i++], args[0]);
		if (!command_path)
			error_exit(MALLOC);
		if (access(command_path, X_OK) == 0)
			break ;
		if (errno == EACCES)
			has_permission_error = 1;
		free(command_path);
	}
	if (!paths || !paths[i] || !command_path)
		handle_command_path_error(args, has_permission_error, paths);
	return (command_path);
}
