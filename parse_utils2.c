/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 22:41:26 by cyang             #+#    #+#             */
/*   Updated: 2025/11/16 14:23:57 by cyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	redir_add_back(t_redir **lst, t_redir *new)
{
	t_redir	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_cmd	*new_cmd(void)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		error_exit(MALLOC);
	node->args = NULL;
	node->redirs = NULL;
	node->next = NULL;
	return (node);
}

t_redir	*new_redir(t_redir_type type, char *target)
{
	t_redir	*node;

	node = malloc(sizeof(t_redir));
	if (!node)
		error_exit(MALLOC);
	node->type = type;
	node->target = ft_strdup(target);
	if (!node->target)
	{
		free(node);
		error_exit(MALLOC);
	}
	node->next = NULL;
	return (node);
}

t_cmd	*check_current_cmd(t_cmd **head_cmd, t_cmd **current)
{
	if (!*current)
	{
		*current = new_cmd();
		if (!*head_cmd)
			*head_cmd = *current;
	}
	return (*current);
}
