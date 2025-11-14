/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:35:42 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/14 01:29:29 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_memcpy(new, old, sizeof(char *) * n);
	new[n] = ft_strdup(token);
	new[n + 1] = NULL;
	free(old);
	cmd->args = new;
}

static int	handle_redirect(char **tokens, int *i, t_cmd **head_cmd, t_cmd **current)
{
	t_redir	*redir;

	check_current_cmd(head_cmd, current);
	if (!tokens[*i + 1] || !is_valid_target(tokens[*i + 1]))
	{
		ft_putendl_fd("minishell: syntax error", 2);
		return (-1);
	}
	redir = new_redir(get_redir_type(tokens[*i]), tokens[*i + 1]);
	redir_add_back(&(*current)->redirs, redir);
	*i = *i + 2;
	return (0);
}

static void	handle_argument(char **tokens, int *i, t_cmd **head_cmd, t_cmd **current)
{
	check_current_cmd(head_cmd, current);
	append_arg(*current, tokens[*i]);
	(*i)++;
}

static void	handle_pipe(t_cmd **head_cmd, t_cmd **current, int *i)
{
	*current = new_cmd();
	cmd_add_back(head_cmd, *current);
	(*i)++;
}

// > < >> << + targetしかない場合の対応
static void	handle_redirect_only(t_cmd *head_cmd)
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

// input: cat input.txt|grep hello >out.txt
t_cmd	*parse_input(char *input)
{
	char	**tokens;
	int		i;
	t_cmd	*head_cmd;
	t_cmd	*current;

	if (!input)
		return (NULL);
	tokens = tokenize(input);
	head_cmd = NULL;
	current = NULL;
	i = 0;
	while (tokens[i])
	{
		if (is_redirect(tokens[i]))
		{
			if (handle_redirect(tokens, &i, &head_cmd, &current) == -1)
			{
				free_all(tokens);
				if (head_cmd)
					free_cmds(head_cmd);
				return (NULL);
			}
		}
		else if (ft_strncmp(tokens[i], "|", 2) == 0)
			handle_pipe(&head_cmd, &current, &i);
		else
			handle_argument(tokens, &i, &head_cmd, &current);
	}
	if (!head_cmd)
		return (ft_putendl_fd("minishell: syntax error", 2), free_all(tokens),
			NULL);
	handle_redirect_only(head_cmd);
	free_all(tokens);
	return (head_cmd);
}

// int	main(void)
// {
// 	t_cmd	*output;
// 	int		i;
// 	char	*str;

// 	str = "ls >> <";
// 	output = parse_input(str);
// 	i = 0;
// 	if (output == NULL)
// 		return (1);
// 	while (output && output->args[i])
// 	{
// 		printf("%s\n", output->args[i]);
// 		i++;
// 	}
// 	if (output->redirs)
// 	{
// 		printf("%u\n", output->redirs->type);
// 		if (output->redirs->target)
// 			printf("%s\n", output->redirs->target);
// 		else if (output->redirs->target == NULL)
// 			printf("target is NULL\n");
// 	}
// 	return (0);
// }
