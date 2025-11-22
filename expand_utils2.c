/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 16:48:52 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/22 16:49:07 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_unused_fd(int fd, t_fds fds)
{
	int	new_fd;

	new_fd = fd + 1;
	if (fds.read_fd == new_fd)
		new_fd++;
	if (fds.write_fd == new_fd)
		new_fd++;
	return (new_fd);
}
