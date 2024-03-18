/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:18:54 by bapasqui          #+#    #+#             */
/*   Updated: 2023/11/07 17:26:01 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*dest;
	int				d;
	unsigned int	c;

	c = 0;
	if (!s)
		return (NULL);
	d = ft_strlen(s);
	dest = malloc(d + 1);
	if (!dest)
		return (NULL);
	while (s[c])
	{
		dest[c] = f(c, s[c]);
		c++;
	}
	dest[c] = '\0';
	return (dest);
}
