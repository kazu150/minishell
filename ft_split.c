/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:45:29 by kaisogai          #+#    #+#             */
/*   Updated: 2025/09/19 00:17:12 by kaisogai         ###   ########.fr       */
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

int	is_letter(const char str, char c)
{
	if (!str)
		return (0);
	if (str == c)
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

static int	count_tokens(const char *str, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (is_letter(*str, c) && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*str == c)
			in_word = 0;
		else if (is_delimiter(*str))
		{
			in_word = 0;
			count++;
			if (is_shift_operator(str))
				str++;
		}
		str++;
	}
	return (count);
}

static void	copy_strs(int word_length, char *strs, const char *str,
		char current_quote)
{
	int	k;
	int	i;

	k = 0;
	i = 0;
	if (current_quote != ' ')
		word_length -= 2;
	while (k < word_length)
	{
		if (is_quote(str[i]) && str[i] == current_quote)
		{
			i++;
			continue ;
		}
		strs[k] = str[i];
		k++;
		i++;
	}
	strs[k] = 0;
}

int	create_new_token(char **strs, const char *str, t_splt s)
{
	if (s.token_len == 0)
		return (1);
	strs[s.j] = malloc(sizeof(char) * (s.token_len + 1));
	if (strs[s.j] == NULL)
		(free_strs(strs, s.j), exit(1));
	copy_strs(s.token_len, strs[s.j], &(str[s.i]), s.current_quote);
	return (s.token_len);
}

void	split_delimiter(char **strs, const char *str, t_splt *s)
{
	while (is_delimiter(str[(*s).i]))
	{
		if (is_shift_operator(&(str[(*s).i])))
			(*s).token_len = 2;
		else
			(*s).token_len = 1;
		(*s).i += create_new_token(strs, str, *s);
		(*s).j++;
	}
}

void	split_arg(char **strs, const char *str, t_splt *s, char c)
{
	int	index;

	index = (*s).token_len + (*s).i;
	while (is_letter(str[(*s).token_len + (*s).i], c) || (*s).inside_quote)
	{
		(*s).token_len++;
		if (!(*s).inside_quote)
			continue ;
		if (str[index] == (*s).current_quote)
			continue ;
		if (is_quote(str[index]))
		{
			(*s).inside_quote = !(*s).inside_quote;
			(*s).current_quote = str[index];
		}
	}
	(*s).i += create_new_token(strs, str, *s);
}

static void	split_tokens(char **strs, const char *str, int str_length, char c)
{
	t_splt	s;

	s.i = 0;
	s.j = 0;
	s.inside_quote = 0;
	while (s.i < str_length)
	{
		split_delimiter(strs, str, &s);
		s.current_quote = ' ';
		s.token_len = 0;
		split_arg(strs, str, &s, c);
		if (s.token_len > 0)
			s.j++;
	}
	strs[s.j] = 0;
}

char	**ft_split(const char *str, char c)
{
	int		tokens_count;
	char	**dest;
	int		i;

	i = 0;
	while (str[i] != 0)
		i++;
	tokens_count = count_tokens(str, c);
	dest = malloc(sizeof(char *) * (tokens_count + 1));
	if (dest == NULL)
		return (NULL);
	split_tokens(dest, str, i, c);
	return (dest);
}

// TODO:
// - "$XXX"のパース処理
// - クオーテーション系のバグ修正（token count失敗、実際に入ってない）

#include "stdio.h"

// int	main(void)
// {
// 	char		**res;
// 	const char	*hoge = "echo aa |  ><<>> <<   'a\".  aa'";

// 	// const char	*hoge1 = "abc          'def'";
// 	// const char	*hoge2 = "abc'          'def";
// 	res = ft_split(hoge, ' ');
// 	printf("%s\n", res[0]);
// 	printf("%s\n", res[1]);
// 	printf("%s\n", res[2]);
// 	printf("%s\n", res[3]);
// 	printf("%s\n", res[4]);
// 	printf("%s\n", res[5]);
// 	printf("%s\n", res[6]);
// 	printf("%s\n", res[7]);
// 	printf("%s\n", res[8]);
// 	// res = ft_split(hoge1, ' ');
// 	// printf("%s\n", res[0]);
// 	// printf("%s\n", res[1]);
// 	// res = ft_split(hoge2, ' ');
// 	// printf("%s\n", res[0]);
// 	// printf("%s\n", res[1]);
// 	free_split(res);
// }
