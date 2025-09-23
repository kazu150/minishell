/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:45:29 by kaisogai          #+#    #+#             */
/*   Updated: 2025/09/23 13:36:20 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_tokens(const char *str, int count, int in_word)
{
	char	current_quote;

	current_quote = ' ';
	while (*str)
	{
		if (is_quote(*str) && current_quote != *str)
			current_quote = *str;
		else if (is_quote(*str) && current_quote == *str)
			current_quote = ' ';
		if (is_letter(*str) && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (!is_letter(*str) && current_quote == ' ')
		{
			in_word = 0;
			if (is_delimiter(*str))
				count++;
			if (is_shift_operator(str))
				str++;
		}
		str++;
	}
	return (count);
}

void	split_delimiter(char **strs, const char *str, t_split *s)
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
	(*s).token_len = 0;
}

void	split_arg(char **strs, const char *str, t_split *s)
{
	int		inside_quote;
	char	current_quote;

	current_quote = ' ';
	inside_quote = 0;
	while (is_letter(str[(*s).token_len + (*s).i]) || inside_quote)
	{
		if (str[(*s).token_len + (*s).i] == current_quote)
			inside_quote = 0;
		else if (current_quote == ' ' && is_quote(str[(*s).token_len + (*s).i]))
		{
			inside_quote = 1;
			current_quote = str[(*s).token_len + (*s).i];
		}
		(*s).token_len++;
	}
	(*s).i += create_new_token(strs, str, *s);
}

static void	split_tokens(char **strs, const char *str, int str_length)
{
	t_split	s;

	s.i = 0;
	s.j = 0;
	while (s.i < str_length)
	{
		split_delimiter(strs, str, &s);
		split_arg(strs, str, &s);
		if (s.token_len > 0)
			s.j++;
	}
	strs[s.j] = 0;
}

char	**tokenize(const char *str)
{
	int		tokens_count;
	char	**dest;
	int		i;

	i = 0;
	while (str[i] != 0)
		i++;
	tokens_count = count_tokens(str, 0, 0);
	dest = malloc(sizeof(char *) * (tokens_count + 1));
	if (dest == NULL)
		return (NULL);
	split_tokens(dest, str, i);
	return (dest);
}

// // TODO:
// // - "$XXX"のパース処理

// #include "stdio.h"

// int	main(void)
// {
// 	char		**res;
// 	const char	*hoge = "echo aa '|'  ><<>> <<   '    a\".  aa'";

// 	// const char	*hoge = " '    a\".  aa'";
// 	// const char	*hoge = "a 'b\".  cd'";
// 	// const char	*hoge1 = "abc          'def'";
// 	// const char	*hoge2 = "abc'          'def";
// 	res = ft_split(hoge);
// 	printf("%s\n", res[0]);
// 	printf("%s\n", res[1]);
// 	printf("%s\n", res[2]);
// 	printf("%s\n", res[3]);
// 	printf("%s\n", res[4]);
// 	printf("%s\n", res[5]);
// 	printf("%s\n", res[6]);
// 	printf("%s\n", res[7]);
// 	printf("%s\n", res[8]);
// 	// printf("%s\n", res[9]);
// 	// printf("%s\n", res[10]);
// 	// res = ft_split(hoge1, ' ');
// 	// printf("%s\n", res[0]);
// 	// printf("%s\n", res[1]);
// 	// res = ft_split(hoge2, ' ');
// 	// printf("%s\n", res[0]);
// 	// printf("%s\n", res[1]);
// 	free_split(res);
// }
