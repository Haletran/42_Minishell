/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:24:13 by ygaiffie          #+#    #+#             */
/*   Updated: 2023/12/28 10:44:15 by ygaiffie         ###   ########.fr       */
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
	while (ft_strchr(set, s1[hold_start]))
		hold_start++;
	i = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[i]))
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
