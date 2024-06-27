/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:14:18 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/27 09:01:00 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"
# include "typedef.h"

//****************************************************************************/
//* census_utils.c

int				gate_or(int i);
t_token_type	add_flag(t_cli *cli, t_token_type type);
int				command_census(t_token *tok, t_cli *cli);
t_token_type	quote_n_heredoc_census(char *token, t_cli *cli);

//****************************************************************************/
//* cleaning_utils.c

void			reindex_token_list(t_cli *cli);
void			replace_last_space(t_token *tok);

//****************************************************************************/
//* organizer.c

int				parsing_organiser(t_cli *cli);

//****************************************************************************/
//* init.c

void			init_organizer(t_cli **cli, char **envp, char **av);
int				first_allocation(t_cli **cli, char **envp);
void			init_fd_history(t_cli **cli);
t_env			*init_stack(t_env *env, char **str);
int				init_data_parsing(t_cli **cli);

//****************************************************************************/
//* init_array.c

int				init_array_env(t_cli **cli, char **envp);
int				init_array(t_cli **cli);

//****************************************************************************/
//* token_type.c

int				ft_lencmparray(char *token, char **array);
int				ft_lenstrtype(char *token, t_cli *cli);
t_token_type	token_type_discovery(char *token, t_cli *cli);
t_token_type	token_type_rediscovery(t_token *tok, t_cli *cli);

//****************************************************************************/

#endif