/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:18:43 by ygaiffie          #+#    #+#             */
/*   Updated: 2023/12/28 10:43:51 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*mod_s1;
	unsigned char	*mod_s2;

	mod_s1 = (unsigned char *)s1;
	mod_s2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while ((mod_s1[i] != '\0' || mod_s2[i] != '\0') && i < n - 1)
	{
		if (mod_s1[i] != mod_s2[i])
			return (mod_s1[i] - mod_s2[i]);
		i++;
	}
	return (mod_s1[i] - mod_s2[i]);
}
