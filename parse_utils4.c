/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 16:11:16 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/22 17:27:09 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_assignment(char *str)
{
	int		i;
	char	*equal_pos;

	if (!str)
		return (0);
	equal_pos = ft_strchr(str, '=');
	if (!equal_pos || equal_pos == str)
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

int	take_off_quotes(char *str)
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
				str[j++] = str[i++];
			if (str[i] == quote)
				i++;
		}
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
	return (has_quote);
}

void	classify_assignments(t_cmd **cmd, int i, int count)
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
