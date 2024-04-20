/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:58:27 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/20 11:40:55 by bapasqui         ###   ########.fr       */
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

#endif