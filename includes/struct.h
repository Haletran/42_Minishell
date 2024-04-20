/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:58:27 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/20 14:16:46 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "lexer.h"

typedef struct s_lst
{
	char			*home_path;
	int				backup[2];
	char			*current_path;
	char			*env_path;
	int				*pid;
	char			**env_var;
	struct s_env	*env_var_lst;
	struct s_env	*env_cpy_lst;
	int				exit_code;
	char			*path_command;
	int				fd[2];
	int				prev_fd[2];
	int				pipe_count;
	char			*infile;
	char			*outfile;
	int				check_if_freed;
	int				file_fd[2];
	int				history_fd;
}					t_lst;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

typedef struct s_arg
{
	char				*arg;
	struct s_arg		*next;
	struct s_arg		*prev;
}						t_arg;
typedef struct s_com
{
	char				*command;
	char				*path;
	t_arg				*arg;
	char				*redirection;
	int					type;
	int					index;
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
	unsigned int		n_token;
	t_token				*token;
	t_com				*com;
	int					index;
	char				**meta;
	char				**redirect;
	char				**control;
	char				**quote;
	int					n_quote;
	char				**bracket;
	char				**commands;
	t_lst				*args;
	t_variable			*variable;

}						t_cli;

#endif