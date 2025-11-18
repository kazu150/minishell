/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 14:27:32 by cyang             #+#    #+#             */
/*   Updated: 2025/11/16 15:55:22 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_arg(t_cmd *cmd, char *token)
{
	char	**old;
	char	**new;
	int		n;

	if (!cmd || !token)
		return ;
	old = cmd->args;
	n = 0;
	while (old && old[n])
		n++;
	new = malloc(sizeof(char *) * (n + 2));
	if (!new)
		error_exit(MALLOC);
	if (old)
		ft_memcpy(new, old, sizeof(char *) * n);
	new[n] = ft_strdup(token);
	new[n + 1] = NULL;
	free(old);
	cmd->args = new;
}

void	handle_argument(char **tokens, int *i, t_cmd **head_cmd,
		t_cmd **current)
{
	check_current_cmd(head_cmd, current);
	append_arg(*current, tokens[*i]);
	(*i)++;
}

void	handle_pipe(t_cmd **head_cmd, t_cmd **current, int *i)
{
	*current = new_cmd();
	cmd_add_back(head_cmd, *current);
	(*i)++;
}

void	handle_redirect_only(t_cmd *head_cmd)
{
	if (head_cmd && !head_cmd->args)
	{
		if (head_cmd->redirs)
		{
			head_cmd->args = malloc(sizeof(char *) * 1);
			if (!head_cmd->args)
				error_exit(MALLOC);
			head_cmd->args[0] = NULL;
		}
	}
}
