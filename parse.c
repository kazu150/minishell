/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:35:42 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/20 18:27:11 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_redirect(char **tokens, int *i, t_cmd **head_cmd,
		t_cmd **current)
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

t_cmd	*parse_input(char *input)
{
	char	**tokens;
	int		i;
	t_cmd	*head_cmd;
	t_cmd	*current;

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
	current = NULL;
	i = 0;
	while (tokens[i])
	{
		if (handle_current_token(tokens, &i, &head_cmd, &current) == -1)
			return (NULL);
	}
	if (!head_cmd)
		return (syntax_error(), free_all(tokens), NULL);
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
