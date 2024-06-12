/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:44:57 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/12 15:30:35 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_dest;
	size_t	len_dest;
	size_t	i;

	if (!s1 || !s2)
		return (0);
	len_dest = (ft_strlen(s1) + ft_strlen(s2) + 1);
	str_dest = (char *)ft_calloc(len_dest, 1);
	if (str_dest == 0)
		return (0);
	i = 0;
	while (*s1 != 0)
	{
		str_dest[i] = *s1++;
		i++;
	}
	while (*s2 != 0)
	{
		str_dest[i] = *s2++;
		i++;
	}
	str_dest[i] = 0;
	return (str_dest);
}
