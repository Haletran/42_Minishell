/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:50:18 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/05 16:13:39 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "typedef.h"

//****************************************************************************/
//* cd.c

void	cd_old_path(t_lst *lst);                 //
void	update_path(t_lst *lst, char *old_path); //
char		*search_path(char *str, t_lst *lst);
int	handle_arguments(char **str, t_lst *lst); //
int			ft_cd(char **str, t_lst *lst);

//****************************************************************************/
//* echo.c

int			handle_n_option(char **str, int *i, int *flag);
int			ft_echo(char **str, t_lst *mnsh, t_cli *cli);

//****************************************************************************/
//* env.c

int			ft_env(t_cli *cli);

//****************************************************************************/
//* exit.c

int			check_code(char *code);
long long	ft_strtoll_check(const char *str);
long long	ft_strtoll(const char *str);
int			ft_exit(char *code, t_cli *cli);
int			ft_exitcode(t_cli *cli, long int exit_code);

//****************************************************************************/
//* export_add.c

int			add_var_no_input(t_lst *mnsh, char **str, int i);
int			add_var(t_lst *mnsh, char **str, int i);
int			add_back(t_lst *mnsh, char **str, int i);

//****************************************************************************/
//* export_chk.c

int			not_existing(t_lst *mnsh, char **str);
int			already_exist(t_lst *mnsh, char **str, int i);
int			check_valid_key(char **str);
int			check_if_var_exist(t_env *env, char *str);
int			check_valid_identifier(char **str);

//****************************************************************************/
//* export.c

char		*expand_var(t_lst *mnsh, char *str);
int			replace_var(t_lst *mnsh, char **str, int i);
int			ft_export(t_lst *mnsh, char **str);

//****************************************************************************/
//* heredoc.c

int			check_number_of_heredoc(t_com *com);
int			check_heredoc_error(t_cli *cli);
void		child_process(t_cli *cli, t_com *com);
int			create_heredoc_file(t_cli **cli);
int			ft_heredoc(t_cli *cli);

//****************************************************************************/
//* pwd.c

int			pwd(t_lst *mnsh, t_cli *cli);

//****************************************************************************/
//* unset.c

void		delete_var(t_lst *mnsh, char *str);
int			ft_unset(char **str, t_lst **mnsh);

//****************************************************************************/
#endif