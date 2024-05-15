/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:58:27 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/15 11:06:09 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "lexer.h"

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
	struct s_env		*prev;
}						t_env;

typedef struct s_lst
{
	t_env				*env_var_lst;
	t_env				*env_cpy_lst;
	char				**env_var;
	char				*home_path;
	char				*current_path;
	char				*env_path;
	char				*path_command;
	int					infile;
	int					outfile;
	int					backup[2];
	int					*pid;
	int					fd[2];
	int					prev_fd[2];
	int					file_fd[2];
	int					pipe_count;
	int					history_fd;
	int					check_if_freed;
	int					exit_code;
	int					nb_heredoc;
	int					heredoc_fd;
	int					heredoc_backup_fd;
	int					heredoc_pipe;
}						t_lst;

typedef struct s_com
{
	char				**command;
	char				*env_path;
	char				*redirection;
	int					type;
	int					index;
	int					pipe;
	struct s_com		*next;
	struct s_com		*prev;
}						t_com;

// TODO Parameter, Tilde, Word Splitting,Globbing
// TODO Possible add order variable in dlst

typedef struct s_variable
{
	char				*key;
	char				*variable;
	int					index;
	struct s_variable	*next;
	struct s_variable	*prev;
}						t_variable;

typedef struct s_token
{
	char				*token;
	t_token_type		type;
	int					index;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_cli
{
	char				*input;
	t_token				*token;
	unsigned int		n_token;
	t_com				*com;
	int					n_com;
	int					index;
	char				**meta;
	char				**redirect;
	char				**control;
	char				**keyword;
	char				**builtin;
	char				**path;
	int					n_quote;
	int					n_dquote;
	char				**bracket;
	char				**commands;
	t_lst				*mnsh;
	t_variable			*variable;
	int					heredoc;
	int					n_variable;
}						t_cli;

#endif