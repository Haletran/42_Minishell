/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:03:47 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/19 08:09:08 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DLST_H
# define DLST_H

# include "minishell.h"
# include "typedef.h"

t_com	*get_last_command(t_com *com);

void	delete_node_com(t_com **head, t_com *del_node);
void	delete_all_nodes_com(t_com **head);
void	insert_com_front(t_com **head, int type, int index);
void	insert_com_after(t_com *prev_node, int type, int index);
void	insert_com_end(t_com **head, int type, int index);

char	*get_token_from_index(t_token *head, int index);
int		get_type_from_token(t_token *head, char *token);
int		get_last_index(t_token *head);
void	print_dlst_token(t_token *head);
t_token	*get_redirection(t_token *head, int start);

void	delete_node_token(t_token **head, t_token *del_node);
void	delete_all_nodes_token(t_token **head);
void	insert_token_front(t_token **head, char *token, t_token_type type,
			int index);
void	insert_token_after(t_token *prev_node, char *token, t_token_type type,
			int index);
void	insert_token_end(t_token **head, char *token, t_token_type type,
			int index);

char	*get_value_from_key(t_env *head, char *key);
char	*get_key_from_value(t_env *head, char *value);
void	print_dlst(t_env *head);

void	delete_node_env(t_env **head, t_env *del_node);
void	delete_all_nodes_env(t_env **head);
void	insert_env_front(t_env **head, char *key, char *value);
void	insert_env_after(t_env *prev_node, char *key, char *value);
void	insert_env_end(t_env **head, char *key, char *value);

char	*get_redirection_file_from_index(t_redirection *head, int index);
int		get_last_index_redi(t_redirection *head);
void	print_dlst_redirection(t_redirection *head);

void	delete_node_redirection(t_redirection **head, t_redirection *del_node);
void	delete_all_nodes_redirection(t_redirection **head);
void	insert_redirection_after(t_redirection *prev_node, char *file,
			t_redi_type type, int index);
void	insert_redirection_front(t_redirection **head, char *file,
			t_redi_type type, int index);
void	insert_redirection_end(t_redirection **head, char *file,
			t_redi_type type, int index);

char	*get_variable_from_key(t_variable *head, char *key);
char	*get_key_from_variable(t_variable *head, char *variable);
int		get_last_index_var(t_variable *head);
void	print_dlst_variable(t_variable *head);

void	delete_node_variable(t_variable **head, t_variable *del_node);
void	delete_all_nodes_variable(t_variable **head);
void	insert_variable_end(t_variable **head, char *key, char *variable,
			int index);
void	insert_variable_after(t_variable *prev_node, char *key, char *variable,
			int index);
void	insert_variable_front(t_variable **head, char *key, char *variable,
			int index);

#endif