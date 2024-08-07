/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_rules.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:02:05 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/07/08 12:17:51 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_RULES_H
# define SYNTAX_RULES_H

# include "minishell.h"
# include "typedef.h"

//****************************************************************************/
//* control_rules.c

void	semi_colon_rules(t_cli *cli, t_token *token);
void	pipe_rules(t_cli *cli, t_token *token);
void	control_rules(t_cli *cli, t_token *token);

//****************************************************************************/
//* redirect_rules.c

void	gt_rules(t_cli *cli, t_token *token);
void	lt_rules(t_cli *cli, t_token *token);
void	redirect_rules(t_cli *cli, t_token *token);

//****************************************************************************/
//* ruler.c

t_token	*prev_selector(t_token *token);
t_token	*next_selector(t_token *token);
void	rulers(t_cli *cli);
void	syntax_error(t_cli *cli, char *token);
void	process_error(t_cli *cli, char *token);

//****************************************************************************/

#endif