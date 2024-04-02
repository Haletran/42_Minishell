/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:07:45 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/04/02 22:15:05 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	count_words(const char *s, char c)
{
	int	n_words;

	n_words = 0;
	while (*s != 0)
	{
		while (*s == c && *s != 0)
			s++;
		if (*s == 0)
			break ;
		while (*s != c && *s != 0)
			s++;
		n_words++;
	}
	return (n_words);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		i;
	int		x;

	x = 0;
	if (!s)
		return (NULL);
	dest = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!dest)
		return (NULL);
	while (*s)
	{
		if (s[0] == c)
			s++;
		else
		{
			i = 0;
			while (s[i] != '\0' && s[i] != c)
				i++;
			dest[x++] = ft_substr(s, 0, i);
			s = s + i;
		}
	}
	dest[x] = NULL;
	return (dest);
}
