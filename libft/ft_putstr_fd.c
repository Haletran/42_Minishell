/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:03:24 by bapasqui          #+#    #+#             */
/*   Updated: 2023/11/22 16:15:39 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	c;

	c = 0;
	if (!s)
		return (ft_putstr_fd("(null)", 1));
	while (s[c] != '\0')
	{
		ft_putchar_fd(s[c], fd);
		c++;
	}
	return (c);
}
