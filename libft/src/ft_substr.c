/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:07:42 by ygaiffie          #+#    #+#             */
/*   Updated: 2023/12/27 11:50:57 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	size;
	char	*sub_str;

	if (!s)
		return (0);
	size = ft_strlen(s);
	if (start > size)
		return (ft_calloc(1, 1));
	if (start + len > size)
		len = size - start;
	sub_str = ft_calloc(len + 1, 1);
	if (sub_str == NULL)
		return (NULL);
	i = -1;
	while (++i < len)
		sub_str[i] = s[i + start];
	sub_str[i] = 0;
	return (sub_str);
}
