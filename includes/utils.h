/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:12:17 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/24 17:40:10 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include "typedef.h"

//****************************************************************************/
//* free.c

void	free_tab(char **str);
void	freeway(t_cli *cli);
char	*free_char(char *str);
void	free_command_line(t_cli *cli);

//****************************************************************************/
//* ft_is.c

int		ft_ismeta(char c);
int		ft_iscontrol(char *token, t_cli *cli);
int		ft_isredirect(char *token, t_cli *cli);
int		ft_isthis(char *this_c, char c);
int		ft_is_error_path(char *str, char **path, t_lst *mnsh, char *full_path);

//****************************************************************************/
//* utils_another.c

void	delete_file(char *name, t_cli *cli);
t_env	*sort_in_ascii(t_env *list);
void	historyze(t_cli *cli);
int		ret_code(t_lst *mnsh, int ret);
void	handle_seg(int signum);

//****************************************************************************/
//* utils_get.c

int		get_exit_code(t_lst *mnsh);
char	*get_env(char *str, t_lst *mnsh);
int		get_nbargs(char **str);
int		get_position_of_next_meta(char *input);

//****************************************************************************/
//* utils_print.c

void	print_list_env(char *string, t_lst *mnsh);
void	print_list_export(t_env *current);
void	print_error(int i, char *str);

//****************************************************************************/

#endif