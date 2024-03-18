/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:05:25 by bapasqui          #+#    #+#             */
/*   Updated: 2023/11/07 16:39:45 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	int	c;

	c = 0;
	if (s == 0)
		return ;
	while (s[c] != 0)
	{
		write(fd, &s[c], 1);
		c++;
	}
	write(fd, "\n", 1);
}
