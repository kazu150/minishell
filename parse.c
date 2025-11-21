/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyang <cyang@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:35:42 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/21 19:37:58 by cyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_assignment(char *str)
{
	int		i;
	char	*equal_pos;

	if (!str)
		return (0);
	equal_pos = ft_strchr(str, '=');
	if(!equal_pos || equal_pos == str)
		return (0);
	if (ft_isdigit(str[0]))
		return (0);
	i = 0;
	while (str + i < equal_pos)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

// parseされた内容をコマンドとassign　それぞれに分類される
static void	separate_assignments(t_cmd *cmd)
{
	int		i;
	int		j;
	int		count;
	char	**new_args;
	t_list	*new_node;

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
			if (count == 0)
			{
				free_all(cmd->args);
				cmd->args = malloc(sizeof(char *));
				if (!cmd->args)
					error_exit(MALLOC);
				cmd->args[0] = NULL;
			}
			else
			{
				new_args = malloc(sizeof(char *) * (count + 1));
				if (!new_args)
					error_exit(MALLOC);
				j = 0;
				while (j < count)
				{
					new_args[j] = ft_strdup(cmd->args[i + j]);
					j++;
				}
				new_args[j] = NULL;
				free_all(cmd->args);
				cmd->args = new_args;
			}
		}
		cmd = cmd->next;
	}
}

static int		take_off_quotes(char *str)
{
	int		i;
	int		j;
	char	quote;
	int		has_quote;

	i = 0;
	j = 0;
	has_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			has_quote = 1;
			quote = str[i++];
			while (str[i] && str[i] != quote)
			{
				str[j++] = str[i++];
			}
			if (str[i] == quote)
				i++;
		}
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
	return (has_quote);
}

static int	handle_redirect(char **tokens, int *i, t_cmd **head_cmd,
		t_cmd **current)
{
	t_redir	*redir;
	int		is_quoted;

	check_current_cmd(head_cmd, current);
	if (!tokens[*i + 1] || !is_valid_target(tokens[*i + 1]))
	{
		ft_putendl_fd("minishell: syntax error", 2);
		return (-1);
	}
	is_quoted = 0;
	if (get_redir_type(tokens[*i]) == R_HDOC)
		is_quoted = take_off_quotes(tokens[*i + 1]);
	redir = new_redir(get_redir_type(tokens[*i]), tokens[*i + 1]);
	redir->heredoc_quote = is_quoted;
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
	separate_assignments(head_cmd);
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
