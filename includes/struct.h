/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:58:27 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/02 19:28:29 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "lexer.h"

typedef struct s_lst
{
	char			*home_path;
	char			*current_path;
	char			*env_path;
	int				*pid;
	char			*username;
	char			*prompt;
	char			**env_var;
	char			**env_cpy;
	struct s_env	**env_var_lst;
	struct s_env 	**env_cpy_lst;
	int				exit_code;
	char			*path_command;
	int *fd;
}					t_lst;

typedef struct s_com
{
	char			*command;
	int				token;
	int				type;
	int				index;
	struct s_com	*next;
}					t_com;


typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;


#endif