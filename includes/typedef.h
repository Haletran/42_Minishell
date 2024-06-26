/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 09:08:12 by bapasqui          #+#    #+#             */
/*   Updated: 2024/07/02 18:54:42 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# include "minishell.h"

typedef enum s_token_type
{
	COMMAND,
	CONTROLE_OPERATOR,
	REDIRECTION_OPERATOR,
	ARGUMENT,
	QUOTE,
	DQUOTE,
	BRACKET,
	FREEZE,
	HEREDOC,
	DELIMITER,
	IMMUTABLE,
	BUILTIN,
	KEYWORD,
	REDIRECTION_ARGUMENT,
	SPACE_HOLDER
}							t_token_type;

typedef enum s_redi_type
{
	IN,
	OUT,
	AND_OUT,
	APPEND_OUT
}							t_redi_type;
typedef struct s_env
{
	char					*key;
	char					*value;
	int						print;
	struct s_env			*next;
	struct s_env			*prev;
}							t_env;

typedef struct s_lst
{
	t_env					*env_var_lst;
	char					**env_var;
	char					*home_path;
	char					*current_path;
	char					*env_path;
	char					*path_command;
	char					*infile;
	char					*outfile;
	int						infile_fd;
	int						outfile_fd;
	int						backup[2];
	int						*pid;
	int						fd[2];
	int						file_fd[2];
	int						pipe_count;
	int						exit_code;
	int						nb_heredoc;
	int						nb_infile;
	int						outfile_check;
	int						infile_check;
	int						heredoc_fd;
	int						heredoc_backup_fd;
	int						heredoc_pipe;
	int						syntax_error;
	int						nb_commands;
	int						not_fork;
	int						ctrl_c;
	int						file_check;
	int						flag_fail;
}							t_lst;

typedef struct s_redirection
{
	t_redi_type				type;
	char					*file;
	int						index;
	struct s_redirection	*next;
	struct s_redirection	*prev;
}							t_redirection;

typedef struct s_com
{
	char					**command;
	char					*env_path;
	t_redirection			*redirection;
	int						type;
	int						index;
	int						pipe;
	struct s_com			*next;
	struct s_com			*prev;
}							t_com;

typedef struct s_variable
{
	char					*key;
	char					*variable;
	int						d_pos;
	int						index;
	struct s_variable		*next;
	struct s_variable		*prev;
}							t_variable;

typedef struct s_token
{
	char					*token;
	t_token_type			type;
	int						index;
	struct s_token			*next;
	struct s_token			*prev;
}							t_token;
typedef struct s_p_exp
{
	struct s_cli			*cli;
	t_token					*tmp;
	t_variable				*var;
	char					*key;
	char					*value;
	int						var_flag;
	int						d_count;
	int						d_pos;
	int						key_len;
}							t_p_exp;

typedef struct s_ccs
{
	t_token					*tmp;
	t_com					*com;
	int						index;
}							t_ccs;

typedef struct s_cli
{
	char					*av;
	int						process_com;
	char					*input;
	t_token					*token;
	t_com					*com;
	unsigned int			n_token;
	int						n_com;
	int						index;
	char					**meta;
	char					**spe_param;
	char					**redirect;
	char					**control;
	char					**keyword;
	char					**builtin;
	char					**path;
	int						flag_quote;
	int						n_dquote;
	int						n_quote;
	int						flag_dquote;
	char					**bracket;
	char					**commands;
	t_lst					*mnsh;
	t_variable				*variable;
	int						heredoc;
	int						rules_flag;
	int						n_variable;
	int						command_flag;
}							t_cli;

#endif