/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:13:23 by ygaiffie          #+#    #+#             */
/*   Updated: 2023/12/28 11:00:18 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	list;
	size_t	len_result;

	if (!format)
		return (0);
	va_start(list, format);
	len_result = 0;
	while (*format)
	{
		if (*format == '%')
		{
			if (*++format == 0)
				return (-1);
			len_result += marshalling(*format, list);
		}
		else
			len_result += ft_putchar(*format);
		format++;
	}
	va_end(list);
	return (len_result);
}

int	marshalling(char c, va_list list)
{
	long long int	len;

	len = 0;
	if (c == 'c')
		len = ft_putchar(va_arg(list, int));
	else if (c == 's')
		len = ft_putstr(va_arg(list, char *));
	else if (c == 'x')
		len = ft_putbase(va_arg(list, size_t), 16, "0123456789abcdef");
	else if (c == 'X')
		len = ft_putbase(va_arg(list, size_t), 16, "0123456789ABCDEF");
	else if (c == 'i' || c == 'd')
		len = ft_putnbr(va_arg(list, int));
	else if (c == 'p')
		len = (ft_putptr(va_arg(list, size_t), 16, "0123456789abcdef"));
	else if (c == 'u')
		len = ft_putnbr(va_arg(list, unsigned int));
	else
		len = ft_putchar(c);
	return (len);
}
