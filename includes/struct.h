/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:58:27 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/09 17:19:06 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "lexer.h"

typedef struct s_lst
{
	char				*home_path;
	int					backup[2];
	char				*current_path;
	char				*env_path;
	int					*pid;
	char				**env_var;
	struct s_env		*env_var_lst;
	struct s_env		*env_cpy_lst;
	int					exit_code;
	char				*path_command;
	int					fd[2];
	int					prev_fd[2];
	int pipe_count;
}						t_lst;

typedef struct s_com
{
	char				*command;
	int					token;
	int					type;
	int					index;
	struct s_com		*next;
}						t_com;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
	struct s_env		*prev;
}						t_env;

typedef struct s_path
{
	char				*path;
	char				*command;
	struct s_env		*next;
}						t_path;

//* *********************************************************************** *//
//* *********************************************************************** *//
//* 																		*//
//* 							CLI STRUCTURE								*//
//* 																		*//
//* *********************************************************************** *//
//* *********************************************************************** *//

//? https://www.gnu.org/software/bash/manual/bash.html
//? https://www.linux.org/threads/bash-01-script-basics.37797/#post-143818
//? https://www.linux.org/threads/bash-02-%E2%80%93-variables-and-such.38200/
//? https://www.linux.org/threads/bash-03-%E2%80%93-command-line-processing.38676/

// TODO Parameter, Tilde, Word Splitting,Globbing
// TODO Possible add order variable in dlst

typedef struct s_variable
{
	char				*key;
	char				*value;
	char				*com_expansion;
	int					index;
	struct s_variable	*next;
	struct s_variable	*prev;
}						t_variable;

typedef struct s_integer
{
	int					*value;
	int					*distri;
	struct s_integer	*next;
	struct s_integer	*prev;
}						t_integer;

typedef struct s_math
{
	struct s_integer	*integer;
	char				*operator;
	int					index;
	struct s_com_sub	*next;
	struct s_com_sub	*prev;
}						t_math;

typedef struct s_token
{
	char				*token;
	int					type;
	int					index;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_meta
{
	char				*meta;
	int					index;
	struct s_meta		*next;
	struct s_meta		*prev;
}						t_meta;

typedef struct s_operator
{
	char				*operator;
	int					index;
	struct s_operator	*next;
	struct s_operator	*prev;
}						t_operator;

typedef struct s_brace
{
	char				*key;
	int					value;
	int					index;
	struct s_brace		*next;
	struct s_brace		*prev;
}						t_brace;

typedef struct s_cli
{
	unsigned int		n_token;
	unsigned int		n_meta;
	unsigned int		n_operator;
	unsigned int		n_brace;
	t_math				*math;
	t_token				*token;
	t_meta				*meta;
	t_operator			*operator;
	t_brace				*brace;
	struct s_cli		*next;
	struct s_cli		*prev;
}						t_cli;

typedef struct s_com_sub
{
	char				*key;
	t_cli				*command;
	char				*value;
	int					index;
	struct s_com_sub	*next;
	struct s_com_sub	*prev;
}						t_com_sub;

#endif