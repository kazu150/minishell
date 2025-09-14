/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:45:29 by kaisogai          #+#    #+#             */
/*   Updated: 2025/09/14 15:15:50 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(const char *str, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*str == c)
			in_word = 0;
		str++;
	}
	return (count);
}

static void	copy_word(int word_length, char *strs, const char *str,
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
		if (is_qt(str[i]) && str[i] == current_quote)
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

int	create_word(char **strs, const char *str, t_splt s)
{
	if (s.w_len == 0)
		return (1);
	strs[s.j] = malloc(sizeof(char) * (s.w_len + 1));
	if (strs[s.j] == NULL)
		(free_strs(strs, s.j), exit(1));
	copy_word(s.w_len, strs[s.j], &(str[s.i]), s.current_qt);
	return (s.w_len);
}

static void	split_words(char **strs, const char *str, int str_length, char c)
{
	t_splt	s;
	int		idx;

	s.i = 0;
	s.j = 0;
	s.inside_qt = 0;
	while (s.i < str_length)
	{
		s.current_qt = ' ';
		s.w_len = 0;
		while ((str[s.w_len + s.i] && str[s.w_len + s.i] != c) || s.inside_qt)
		{
			idx = s.w_len + s.i;
			if (is_qt(str[idx]) && !(s.inside_qt && str[idx] != s.current_qt))
			{
				s.inside_qt = !s.inside_qt;
				s.current_qt = str[idx];
			}
			s.w_len++;
		}
		s.i += create_word(strs, str, s);
		if (s.w_len > 0)
			s.j++;
	}
	strs[s.j] = 0;
}

char	**ft_split(const char *str, char c)
{
	int		strs_count;
	char	**dest;
	int		i;

	strs_count = 1;
	i = 0;
	while (str[i] != 0)
		i++;
	strs_count = count_words(str, c);
	dest = malloc(sizeof(char *) * (strs_count + 1));
	if (dest == NULL)
		return (NULL);
	split_words(dest, str, i, c);
	return (dest);
}

// #include "stdio.h"

// int	main(void)
// {
// 	const char	*hoge = "echo 'a\"aa'";
// 	char		**res;

// 	// const char	*hoge1 = "abc          'def'";
// 	// const char	*hoge2 = "abc'          'def";
// 	res = ft_split(hoge, ' ');
// 	printf("%s\n", res[0]);
// 	printf("%s\n", res[1]);
// 	// res = ft_split(hoge1, ' ');
// 	// printf("%s\n", res[0]);
// 	// printf("%s\n", res[1]);
// 	// res = ft_split(hoge2, ' ');
// 	// printf("%s\n", res[0]);
// 	// printf("%s\n", res[1]);
// }
