/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 23:01:11 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/07/01 20:18:12 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	split_into_token(t_cli *cli)
{
	int		i;
	int		offset;
	char	*token_tmp;

	cli->n_token = get_last_index(cli->token) + 1;
	i = 0;
	while (i < (int)ft_strlen(cli->input) && cli->input[i] != 0)
	{
		if (ft_isthis("\n\t", cli->input[i]))
			i++;
		if (cli->input[i] == 0)
			break ;
		offset = ft_lenstrtype(cli->input + i, cli);
		if (ft_isthis(" '\"\t\n", cli->input[i]))
			offset++;
		if (offset == 0)
			offset = get_position_of_next_meta(cli->input + i);
		token_tmp = ft_substr(cli->input, i, offset);
		if (token_tmp == NULL)
			return ;
		insert_token_end(&cli->token, ft_strdup(token_tmp),
			token_type_discovery(token_tmp, cli), cli->n_token++);
		free_char(token_tmp);
		i += offset;
	}
}
