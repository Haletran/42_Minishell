/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:13:32 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/04/02 22:21:50 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_bool	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (TRUE);
	return (FALSE);
}
