/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:35:42 by kaisogai          #+#    #+#             */
/*   Updated: 2025/09/14 17:32:46 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// input: cat input.txt|grep hello >out.txt
t_cmd	*parse_input(char *input)
{
	char **words;
	int i;
	t_cmd *cmd;

	words = ft_split(input, ' ');
	i = 0;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		exit(MALLOC);
	cmd->args = NULL;
	cmd->next = NULL;
	cmd->redirs = NULL;
	while (words)
	{
		if (is_redir(words[i]))
		{
			// words[i]がREDIRなら、現在のnodeのredirsに追加
			if (!cmd->redirs)
				cmd->redirs = malloc(sizeof(t_redir));
			cmd->redirs->type = words[i];
			cmd->redirs->target = words[i + 1];
			cmd->redirs->next = NULL;
		}
		else if (ft_strncmp(words[i], "|", 2) == 0)
		{
			// words[i]がPIPEなら、次のnodeを作成
			cmd->next = malloc(sizeof(t_cmd));
			if (!cmd)
				exit(MALLOC);
			cmd->args = NULL;
			cmd->next = NULL;
			cmd->redirs = NULL;
		}
		else
		{
			// words[i]が上記以外なら、現在のnodeのargsに追加
			if (!cmd->args)
				cmd->args = malloc(sizeof(char **));
			cmd->args = words[i];
			cmd->args++;
		}
		i++;
	}
}