/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:14:18 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/05 14:18:10 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"
# include "typedef.h"

//****************************************************************************/
//* organizer.c

void	parsing_organiser(t_cli *cli);

//****************************************************************************/
//* init.c

void	init_organizer(t_cli **cli, char **envp);
int		first_allocation(t_cli **cli, char **envp);
void	init_fd_history(t_cli **cli);
t_env	*init_stack(t_env *env, char **str);
int		init_data_parsing(t_cli **cli);

//****************************************************************************/
//* init_array.c

int		init_array_env(t_cli **cli, char **envp);
int		init_array(t_cli **cli);

//****************************************************************************/

#endif