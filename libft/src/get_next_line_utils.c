/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:00:35 by ygaiffie          #+#    #+#             */
/*   Updated: 2023/12/27 11:52:08 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin_f(char *s1, char *s2)
{
	char	*str_dest;
	size_t	len_dest;
	size_t	i;
	size_t	j;

	if (!s1)
		return (NULL);
	len_dest = (ft_strlen(s1) + ft_strlen(s2) + 1);
	str_dest = ft_calloc(len_dest, 1);
	if (str_dest == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j] != '\0')
		str_dest[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		str_dest[i++] = s2[j++];
	str_dest[i] = '\0';
	free(s1);
	return (str_dest);
}
