/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:52:46 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/05/15 07:40:47 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_itoa(int n)
{
	int		i;
	int		mod_n;
	char	*n_str;

	mod_n = n;
	i = ft_intlen(n, 0);
	if (n == -2147483648)
		mod_n++;
	if (n < 0)
		mod_n = -mod_n;
	n_str = (char *)ft_calloc(sizeof(char), i + 1);
	if (!n_str)
		return (NULL);
	while (i > 0)
	{
		i--;
		n_str[i] = (mod_n % 10) + 48;
		mod_n /= 10;
	}
	if (n < 0)
		n_str[i] = '-';
	if (n == -2147483648)
		n_str[ft_intlen(n, 0) - 1] += 1;
	return (n_str);
}
