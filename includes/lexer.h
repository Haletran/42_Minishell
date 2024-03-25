/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:46:22 by bapasqui          #+#    #+#             */
/*   Updated: 2024/03/20 17:22:47 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum s_tokens
{
	QUOTES,
	S_QUOTES,
	COMMAND,
	ARG,
	PIPE,
	PATH,
	EXEC,
}	t_tokenType;

#endif