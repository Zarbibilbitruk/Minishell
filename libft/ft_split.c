/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:52:23 by afontele          #+#    #+#             */
/*   Updated: 2023/12/11 13:19:38 by afontele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	num_of_words;
	size_t	i;

	num_of_words = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			num_of_words++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (num_of_words);
}

static size_t	word_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0' && s[len] != c)
		len++;
	return (len);
}

static void	free_array(size_t i, char **array)
{
	while (i > 0)
	{
		i--;
		free(array[i]);
	}
	free(array);
}

static char	**split(char const *s, char c, char **array, size_t words_count)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < words_count)
	{
		while (s[j] != '\0' && s[j] == c)
			j++;
		array[i] = ft_substr(s, j, word_len(s + j, c));
		if (!array[i])
		{
			free_array(i, array);
			return (NULL);
		}
		while (s[j] != '\0' && s[j] != c)
			j++;
		i++;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array_of_str;
	size_t	words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	array_of_str = (char **)malloc(sizeof(char *) * (words + 1));
	if (!array_of_str)
		return (NULL);
	array_of_str = split(s, c, array_of_str, words);
	return (array_of_str);
}
