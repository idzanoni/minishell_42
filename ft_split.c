/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:36:19 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/06/24 15:27:05 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void new_prompt(char *prompt)
{
	int		count;
	char	quote;

	count = 0;
	while(prompt[count] != '\0')
	{
		if(prompt[count] == '"' || prompt[count] == '\'')
		{
			quote = prompt[count];
			count++;
			while(prompt[count] != quote)
				count++;
			count++;
		}
		else
		{
			while(prompt[count] != ' ' && prompt[count] != '\0' && prompt[count] != '	')
				count++;
			if (prompt[count] == ' ' || prompt[count] == '	')
			{
				prompt[count] = -42;
				count++;
			}
		}
	}
}

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
	//printf("é o que veio: %s\n", s);
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
