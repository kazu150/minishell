/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:35:42 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/22 16:42:04 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void classify_assignments(t_cmd **cmd, int i, int count)
{
	char	**new_args;
	int		j;

	if (count == 0)
	{
		free_all((*cmd)->args);
		(*cmd)->args = malloc(sizeof(char *));
		if (!(*cmd)->args)
			error_exit(MALLOC);
		(*cmd)->args[0] = NULL;
		return ;
	}
	new_args = malloc(sizeof(char *) * (count + 1));
	if (!new_args)
		error_exit(MALLOC);
	j = 0;
	while (j < count)
	{
		new_args[j] = ft_strdup((*cmd)->args[i + j]);
		j++;
	}
	new_args[j] = NULL;
	free_all((*cmd)->args);
	(*cmd)->args = new_args;
}

static void	separate_assignments(t_cmd *cmd)
{
	int		i;
	t_list	*new_node;
	int		count;

	while (cmd)
	{
		i = 0;
		while (cmd->args && cmd->args[i] && is_assignment(cmd->args[i]))
		{
			new_node = ft_lstnew(ft_strdup(cmd->args[i]));
			if (!new_node)
				error_exit(MALLOC);
			ft_lstadd_back(&cmd->assigns, new_node);
			i++;
		}
		if (i > 0)
		{
			count = 0;
			while (cmd->args[i + count])
				count++;
			classify_assignments(&cmd, i, count);
		}
		cmd = cmd->next;
	}
}

int	handle_current_token(char **tokens, int *i, t_cmd **head_cmd,
		t_cmd **current)
{
	if (is_redirect(tokens[*i]))
	{
		if (handle_redirect(tokens, i, head_cmd, current) == -1)
		{
			free_all(tokens);
			free_cmds(head_cmd);
			return (-1);
		}
	}
	else if (ft_strncmp(tokens[*i], "|", 2) == 0)
		handle_pipe(head_cmd, current, i);
	else
		handle_argument(tokens, i, head_cmd, current);
	return (0);
}

static int	invalid_pipe_syntax(char **tokens)
{
	int	i;

	if (!tokens || !tokens[0])
		return (0);
	if (ft_strcmp(tokens[0], "|") == 0)
		return (1);
	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "||") == 0)
			return (1);
		if (ft_strcmp(tokens[i], "|") == 0)
		{
			if (!tokens[i + 1] || ft_strcmp(tokens[i + 1], "|") == 0)
				return (1);
		}
		i++;
	}
	return (0);
}

int	parse_tokens(char **tokens, t_cmd **head_cmd)
{
	int		i;
	t_cmd	*current;

	i = 0;
	current = NULL;
	while (tokens[i])
	{
		if (handle_current_token(tokens, &i, head_cmd, &current) == -1)
			return (1);
	}
	if (!*head_cmd)
		return (syntax_error(), free_all(tokens), 1);
	handle_redirect_only(*head_cmd);
	separate_assignments(*head_cmd);
	free_all(tokens);
	return (0);
}

t_cmd	*parse_input(char *input)
{
	char	**tokens;
	t_cmd	*head_cmd;
	int		has_error;

	if (!input)
		return (NULL);
	tokens = tokenize(input);
	if (!tokens)
		return (0);
	if (invalid_pipe_syntax(tokens))
	{
		syntax_error();
		free_all(tokens);
		return (NULL);
	}
	head_cmd = NULL;
	has_error = parse_tokens(tokens, &head_cmd);
	if (has_error)
		return (NULL);
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
