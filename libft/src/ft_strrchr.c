/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:17:20 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/02 22:17:21 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	mod_c;
	int				i;

	mod_c = c;
	i = ft_strlen((char *)s);
	if (s[i] == mod_c)
		return ((char *)s + i);
	while (i--)
		if (s[i] == mod_c)
			return ((char *)s + i);
	return (NULL);
}
