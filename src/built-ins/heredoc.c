/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:42:19 by bapasqui          #+#    #+#             */
/*   Updated: 2024/03/18 14:01:37 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_heredoc(char **str)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (!ft_strncmp(input, str[1], ft_strlen(str[1]))
			&& ft_strlen(str[1]) == ft_strlen(input))
			return (SUCCESS);
	}
	return (ERROR);
}
