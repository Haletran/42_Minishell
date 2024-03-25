/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:58:27 by bapasqui          #+#    #+#             */
/*   Updated: 2024/03/25 14:08:23 by bapasqui         ###   ########.fr       */
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

#endif