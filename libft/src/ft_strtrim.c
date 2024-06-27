/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:24:13 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/27 21:15:21 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimed_str;
	int		hold_start;
	int		i;
	int		j;

	if (!s1)
		return (NULL);
	hold_start = 0;
	while (s1[hold_start] && ft_strchr(set, s1[hold_start]))
		hold_start++;
	i = ft_strlen(s1) - 1;
	while (i >= hold_start && ft_strchr(set, s1[i]))
		i--;
	i = i - hold_start + 1;
	if (i < 0)
		i = 0;
	trimed_str = (char *)ft_calloc(sizeof(char), (i + 1));
	if (!trimed_str)
		return (NULL);
	j = 0;
	while (i--)
		trimed_str[j++] = s1[hold_start++];
	return (trimed_str);
}
