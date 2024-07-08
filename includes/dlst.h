/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:03:47 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/07/08 16:38:22 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DLST_H
# define DLST_H

# include "minishell.h"
# include "typedef.h"

//****************************************************************************/
//* dlst_command_get.c

t_com	*get_last_command(t_com *com);

//****************************************************************************/
//* dlst_command_insert.c

void	insert_com_front(t_com **head, int type, int index);
void	insert_com_after(t_com *prev_node, int type, int index);
void	insert_com_end(t_com **head, int type, int index);

//****************************************************************************/
//* dlst_command_del.c

void	delete_node_redi(t_redirection **head, t_redirection *del_node);
void	delete_all_nodes_redi(t_redirection **head);
void	*delete_node_com(t_com **head, t_com *del_node);
void	delete_all_nodes_com(t_com **head);

//****************************************************************************/
//* dlst_env_get.c

int		get_env_size(t_env *head);
int		find_in_env(char *str, t_cli *cli);
char	*get_value_from_key(t_env *head, char *key);
char	*get_key_from_value(t_env *head, char *value);
t_env	*get_env_var(t_env *env, char *key);

//****************************************************************************/
//* dlst_env_set.c

void	delete_node_env(t_env **head, t_env *del_node);
void	delete_all_nodes_env(t_env **head);
void	insert_env_front(t_env **head, char *key, char *value);
void	insert_env_after(t_env *prev_node, char *key, char *value);
void	insert_env_end(t_env **head, char *key, char *value, int print);

//****************************************************************************/
//* dlst_redir_get.c

char	*get_redirection_file_from_index(t_redirection *head, int index);
int		get_last_index_redi(t_redirection *head);

//****************************************************************************/
//* dlst_redir_set.c

void	delete_node_redirection(t_redirection **head, t_redirection *del_node);
void	delete_all_nodes_redirection(t_redirection **head);
void	insert_redirection_front(t_redirection **head, char *file,
			t_redi_type type, int index);
void	insert_redirection_after(t_redirection *prev_node, char *file,
			t_redi_type type, int index);
void	insert_redirection_end(t_redirection **head, char *file,
			t_redi_type type, int index);

//****************************************************************************/
//* dlst_token_get.c

char	*get_token_from_index(t_token *head, int index);
int		get_type_from_token(t_token *head, char *token);
int		get_last_index(t_token *head);
void	print_dlst_token(t_token *head);
t_token	*get_redirection(t_token *head, int start);

//****************************************************************************/
//* dlst_token_set.c

void	delete_node_token(t_token **head, t_token *del_node);
void	delete_all_nodes_token(t_token **head);
void	insert_token_front(t_token **head, char *token, t_token_type type,
			int index);
void	insert_token_after(t_token *prev_node, char *token, t_token_type type,
			int index);
void	insert_token_end(t_token **head, char *token, t_token_type type,
			int index);

//****************************************************************************/
//* dlst_variable_get.c

char	*get_variable_from_key(t_variable *head, char *key);
char	*get_key_from_variable(t_variable *head, char *variable);
int		get_last_index_var(t_variable *head);
void	print_dlst_variable(t_variable *head);

//****************************************************************************/
//* dlst_variable_set.c

void	delete_node_variable(t_variable **head, t_variable *del_node);
void	delete_all_nodes_variable(t_variable **head);
void	insert_variable_front(t_variable **head, char *key, char *variable,
			int index);
void	insert_variable_after(t_variable *prev_node, char *key, char *variable,
			int index);
void	insert_variable_end(t_variable **head, char *key, char *variable,
			int index);

//****************************************************************************/

#endif