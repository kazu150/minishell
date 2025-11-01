/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:45:29 by kaisogai          #+#    #+#             */
/*   Updated: 2025/11/01 15:39:47 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

static int	free_strs(char **strs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (0);
}

static void	copy_word(int word_length, char *strs, const char *str, int i)
{
	int	k;

	k = 0;
	while (k < word_length)
	{
		strs[k] = str[i];
		k++;
		i++;
	}
	strs[k] = 0;
}

static int	split_words(char **strs, const char *str, int str_length, char c)
{
	int	i;
	int	word_length;
	int	j;

	i = 0;
	j = 0;
	while (i < str_length)
	{
		word_length = 0;
		while (str[word_length + i] && str[word_length + i] != c)
			word_length++;
		if (word_length > 0)
		{
			strs[j] = malloc(sizeof(char) * (word_length + 1));
			if (strs[j] == NULL)
				return (free_strs(strs, j));
			copy_word(word_length, strs[j], str, i);
			j++;
			i += word_length;
		}
		else
			i++;
	}
	strs[j] = 0;
	return (1);
}

char	**ft_split(const char *str, char c)
{
	int		strs_count;
	char	**dest;
	int		i;
	int		has_no_error;

	i = 0;
	while (str[i] != 0)
		i++;
	strs_count = count_words(str, c);
	dest = malloc(sizeof(char *) * (strs_count + 1));
	if (dest == NULL)
		return (NULL);
	has_no_error = split_words(dest, str, i, c);
	if (!has_no_error)
		return (NULL);
	return (dest);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char str[] = "ki   aeiueokakikukekosasisuseso   k";
// 	char c = 'k';
// 	char **dest = ft_split(str, c);
// 	if (dest == NULL)
// 		return (0);
// 	int i = 0;
// 	while (dest[i] != 0)
// 	{
// 		printf("%s\n", dest[i]);
// 		i++;
// 	}
// }