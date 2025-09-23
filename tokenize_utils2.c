/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:53:20 by kaisogai          #+#    #+#             */
/*   Updated: 2025/09/23 13:36:45 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_delimiter(char str)
{
	if (str == '|')
		return (1);
	if (str == '<')
		return (1);
	if (str == '>')
		return (1);
	return (0);
}

int	is_letter(const char str)
{
	if (!str)
		return (0);
	if (str == ' ')
		return (0);
	if (is_delimiter(str))
		return (0);
	return (1);
}

int	is_shift_operator(const char *str)
{
	if (ft_strncmp("<<", str, 2) == 0)
		return (1);
	if (ft_strncmp(">>", str, 2) == 0)
		return (1);
	return (0);
}

void	copy_strs(int word_length, char *strs, const char *str)
{
	int	k;
	int	i;

	k = 0;
	i = 0;
	while (k < word_length)
	{
		strs[k] = str[i];
		k++;
		i++;
	}
	strs[k] = 0;
}

int	create_new_token(char **strs, const char *str, t_split s)
{
	if (s.token_len == 0)
		return (1);
	strs[s.j] = malloc(sizeof(char) * (s.token_len + 1));
	if (strs[s.j] == NULL)
		(free_strs(strs, s.j), exit(1));
	copy_strs(s.token_len, strs[s.j], &(str[s.i]));
	return (s.token_len);
}
