/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:58:46 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/24 17:40:05 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_LINE_H
# define COMMAND_LINE_H

# include "minishell.h"
# include "typedef.h"

//****************************************************************************/
//* cleaning_dlst_token.c

void		remove_quotes(t_cli *cli);
int			glue_quotes(t_cli *cli);
void		cleaning_token_list(t_cli *cli);
void		concat_no_space(t_cli *cli);
void		delete_n_token(t_token **head, int n);

//****************************************************************************/
//* create_command.c

char		*return_path(char *str, t_cli **cli);
void		fill_command(t_cli *cli, t_token *tmp, t_com *com);
char		**cpy_env(t_cli *cli);
void		create_command(t_cli *cli);
int			get_nb_args(t_token *head);

//****************************************************************************/
//* create_redirection.c

t_redi_type	redirection_census(char *token);
void		handle_redir(t_token *tmp, t_com *com, int *i);
void		create_redirection(t_cli *cli);

//****************************************************************************/
//* input_reader.c

void		exit_input(t_cli *cli);
void		input_reader(t_cli *cli);

//****************************************************************************/
//* parameter_expansion.c

void		replacement(t_token *tmp, char *value, char *key,
				int str_token_len);
char		*get_parameter_value(t_cli *cli, char *key);
int			variable_len(char *token);
int			dollar_position(char *token);
void		parameter_expansion(t_cli *cli);

//****************************************************************************/
//* split_into_token.c

void		split_into_token(t_cli *cli);

//****************************************************************************/
//* tilde_expansion.c

void		tilde_expansion_process(t_token *tmp, char c, char *env_var);
void		tilde_expansion(t_cli *cli);

//****************************************************************************/
//* varloc_creation.c

int			varloc_creation(t_cli *cli);
int			varloc_modify(t_cli *cli, char *key_line, char *var_line);
int			varloc_attrib(t_cli *cli, char *key_line, char *var_line,
				int index);
char		*key_from_token(char *token);
char		*variable_from_token(char *token);

//****************************************************************************/

#endif