/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:45:55 by ygaiffie          #+#    #+#             */
/*   Updated: 2023/12/28 10:43:59 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*str_process;

	if (!s || !f)
		return (NULL);
	str_process = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!str_process)
		return (NULL);
	i = -1;
	while (s[++i])
		str_process[i] = f(i, s[i]);
	str_process[i] = 0;
	return (str_process);
}
