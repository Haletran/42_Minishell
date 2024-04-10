/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:53:37 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/04/02 22:18:09 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str || !fd)
		return (-1);
	while (*str != 0)
		i += write(fd, str++, 1);
	return (i);
}
