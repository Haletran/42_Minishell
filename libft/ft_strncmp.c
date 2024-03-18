/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:21:47 by bapasqui          #+#    #+#             */
/*   Updated: 2023/11/07 17:26:04 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			a;
	size_t			b;
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	a = 0;
	b = 0;
	tmp1 = (unsigned char *)s1;
	tmp2 = (unsigned char *)s2;
	while ((tmp1[a] != '\0' || tmp2[a] != '\0') && b < n)
	{
		if (tmp1[a] != tmp2[a])
			return (tmp1[a] - tmp2[a]);
		a++;
		b++;
	}
	return (0);
}
