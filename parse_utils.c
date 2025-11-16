/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 22:38:03 by cyang             #+#    #+#             */
/*   Updated: 2025/11/16 14:46:54 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	message_exit(char *message, int exit_type)
{
	printf("%s\n", message);
	exit(exit_type);
}

void	free_exit(void *target)
{
	free(target);
	exit(EXIT_SUCCESS);
}

int	is_redirect(char *s)
{
	if (!ft_strncmp(s, ">", 2) || !ft_strncmp(s, "<", 2) || !ft_strncmp(s, ">>",
			3) || !ft_strncmp(s, "<<", 3))
		return (1);
	else
		return (0);
}

t_redir_type	get_redir_type(char *token)
{
	if (ft_strncmp(token, "<", 2) == 0)
		return (R_IN);
	if (ft_strncmp(token, ">", 2) == 0)
		return (R_OUT);
	if (ft_strncmp(token, ">>", 3) == 0)
		return (R_APP);
	if (ft_strncmp(token, "<<", 3) == 0)
		return (R_HDOC);
	return (R_NONE);
}

int	is_valid_target(char *s)
{
	if (!s)
		return (0);
	else if (ft_strncmp(s, "|", 2) == 0)
		return (0);
	else if (is_redirect(s))
		return (0);
	else
		return (1);
}
