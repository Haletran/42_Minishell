/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:52:52 by bapasqui          #+#    #+#             */
/*   Updated: 2024/03/20 11:40:00 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	show_token(char **commands, t_com **com)
{
	(void)com;
	/* 	int i;

		i = 0;
		t_com *head;
		com = malloc(1000);
		head = (*com);

		while (commands[i])
		{
			*com = malloc(100);

			printf("%c TOKEN IS %d", input[i], (*com)->token);
			(*com) = (*com)->next;
			i++;
		}
		(*com) = head;
	} */
	print_commands(commands);
}
