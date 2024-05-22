/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleite-s <rleite-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:56:25 by izanoni           #+#    #+#             */
/*   Updated: 2024/05/21 18:29:38 by rleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words1(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s != '\0')
			count++;
		while (*s != '\0' && *s != c)
			s++;
	}
	return (count);
}

char	*get_word1(char const *s, char c)
{
	char	*word;
	int		len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	word[len] = '\0';
	while (len--)
		word[len] = s[len];
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**splited_str;
	int		nb_words;
	int		i;

	if (!s)
		return (NULL);
	nb_words = count_words1(s, c);
	splited_str = (char **)malloc((nb_words + 1) * sizeof(char *));
	if (!splited_str)
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s != '\0')
			splited_str[i++] = get_word1(s, c);
		while (*s != '\0' && *s != c)
			s++;
	}
	splited_str[i] = NULL;
	return (splited_str);
}
