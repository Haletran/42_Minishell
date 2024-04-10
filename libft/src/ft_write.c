/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:10:30 by ygaiffie          #+#    #+#             */
/*   Updated: 2023/12/28 10:59:54 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

size_t	ft_putstr(char *str)
{
	size_t	i;

	if (str == 0)
		str = "(null)";
	i = 0;
	while (str[i] != 0)
		write(1, &str[i++], 1);
	return (i);
}

size_t	ft_putbase(unsigned int nbr, int base, char *table)
{
	char	r[17];
	size_t	i;

	i = 0;
	ft_bzero(r, 17);
	if (nbr == 0)
		return (write(1, "0", 1));
	while (nbr > 0)
	{
		r[i++] = table[nbr % base];
		nbr /= base;
	}
	if (i == 17)
		i--;
	ft_rev_wr(r);
	return (i);
}

size_t	ft_putnbr(long long nb)
{
	size_t		i;
	char		r[19];
	long long	mod_nb;

	mod_nb = nb;
	ft_bzero(r, 19);
	i = 0;
	if (nb == 0)
		return (write(1, "0", 1));
	if (nb < 0)
		nb = -nb;
	while (nb > 0)
	{
		r[i++] = (nb % 10) + 48;
		nb /= 10;
	}
	if (mod_nb < 0)
		r[i++] = '-';
	if (i == 20)
		i--;
	ft_rev_wr(r);
	return (i);
}

size_t	ft_putptr(size_t nbr, int base, char *table)
{
	char	r[17];
	size_t	i;

	i = 0;
	ft_bzero(r, 17);
	if (nbr == 0)
		return (write(1, "(nil)", 5));
	write(1, "0x", 2);
	while (nbr > 0)
	{
		r[i++] = table[nbr % base];
		nbr /= base;
	}
	if (i == 17)
		i--;
	ft_rev_wr(r);
	return (i + 2);
}
