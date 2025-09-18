/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:35:42 by kaisogai          #+#    #+#             */
/*   Updated: 2025/09/18 12:04:58 by cyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_all(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static int	is_redirect(char *s)
{
	if (!ft_strncmp(s, ">", 2) || !ft_strncmp(s, "<", 2) || !ft_strncmp(s, ">>", 3) || !ft_strncmp(s, "<<", 3))
		return (1);
	else
		return (0);
}

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

void	add_redir_back(t_redir **lst, t_redir *new)
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

static t_cmd	*new_cmd(void)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		error_exit(MALLOC);
	node->args = NULL;
	node->redirs= NULL;
	node->next = NULL;
	return (node);
}

static t_redir	*new_redir(t_redir_type type, char *target)
{
	t_redir	*node;

	node = malloc(sizeof(t_redir));
	if (!node)
		error_exit(MALLOC);
	node->type = type;
	node->target = target;
	node->next = NULL;
	return (node);
}

static void	append_arg(t_cmd *cmd, char *token)
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
		ft_memcpy(new, old, sizeof(char*) * n);
	new[n] = ft_strdup(token);
	new[n + 1] = NULL;
	free(old);
	cmd->args = new;
}

static t_redir_type	get_redir_type(char *token)
{
	if (ft_strncmp(token, "<", 2) == 0)
		return (R_IN);
	if (ft_strncmp(token, ">", 2) == 0)
		return (R_OUT);
	if (ft_strncmp(token, ">>", 3) == 0)
		return (R_APP);
	if (ft_strncmp(token, "<<", 3) == 0)
		return (R_HDOC);
}

// input: cat input.txt|grep hello >out.txt
t_cmd	*parse_input(char *input)
{
	char 	**tokens;
	int 	i;
	t_cmd	*head_cmd;
	t_cmd	*current;

	if (!input)
		return (NULL);
	//新しいバージョンft_splitを入れ替え
	tokens = ft_split(input, ' ');
	// char	*tokens[] = {"ls", "|", "cat"};
	head_cmd = NULL;
	current = NULL;
	i = 0;
	while (tokens[i])
	{
		if (is_redir(tokens[i]))
		{
			// words[i]がREDIRなら、現在のnodeのredirsに追加
			//redirectの後に必ずtargetがくるそうです
			if (!tokens[i + 1])
			{
				ft_putendl_fd("minishell: syntax error", 2);
				free_all(tokens);
				return (NULL);
			}
			t_redir *redir = new_redir(get_redir_type(tokens[i]), tokens[i + 1]);
			add_redir_back(&current->redirs, redir);
			i = i + 2;
		}
		else if (ft_strncmp(tokens[i], "|", 2) == 0)
		{
			// words[i]がPIPEなら、次のnodeを作成
			current = new_cmd();
			add_cmd_back(&head_cmd, current);
			i++;
		}
		else
		{
			// words[i]が上記以外なら、現在のnodeのargsに追加
			// currentがNULLですとクラッシュしますので、まずcurrentがNULL出ないように操作
			if (!current)
			{
				current = new_cmd();
				if (!head_cmd)
					head_cmd = current;
			}
			append_arg(current, tokens[i]);
			i++;
		}
	}
}
