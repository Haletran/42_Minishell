/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:50:18 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/20 10:56:44 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "typedef.h"

//****************************************************************************/
//* cd_utils.c

int			return_process(int exit_code, char *old_path, t_lst *lst);
int			cd_valid(int valid, char **str, char *old_path, t_lst *lst);

//****************************************************************************/
//* cd.c

void		cd_old_path(t_lst *lst);
void		update_path(t_lst *lst, char *old_path);
char		*search_path(char *str, t_lst *lst);
int			handle_arguments(char **str, t_lst *lst);
int			ft_cd(char **str, t_lst *lst);

//****************************************************************************/
//* echo.c

int			handle_n_option(char **str, int *i, int *flag);
void		echo_print(char **str, int i);
int			ft_echo(char **str, t_lst *mnsh, t_cli *cli);

//****************************************************************************/
//* env.c

int			ft_env(t_cli *cli);

//****************************************************************************/
//* exit_utils.c

int			ft_exit_process(int exit_code, t_cli *cli);

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
void		env_dup(t_env *env, char *value, char *to_keep, char **tmp);
int			add_back(t_lst *mnsh, char **str, int i);

//****************************************************************************/
//* export_chk.c

int			not_existing(t_lst *mnsh, char **str);
int			already_exist(t_lst *mnsh, char **str, int i);
int			check_valid_key(char **str);
int			check_if_var_exist(t_env *env, char *str);
int			check_valid_identifier(char **str);

//****************************************************************************/
//* export_utils.c

void		chk_tmp(t_env *env, char **tmp);
t_env		*cpy_env_var(t_env *cpy);
void		add_process(t_lst *mnsh, char **str, int i, int *err);
void		cpy_process(t_lst *mnsh);

//****************************************************************************/
//* export.c

char		*expand_var(t_lst *mnsh, char *str);
int			replace_var(t_lst *mnsh, char **str, int i);
int			ft_export(t_lst *mnsh, char **str);

//****************************************************************************/
//* heredoc_child.c

char		*handle_eof(char *input, int line_count, t_com *com, t_cli *cli);
char		*handle_sigint(char *input, t_cli *cli);
void		write_to_heredoc(char *input, t_cli *cli);
char		*handle_heredoc_end(char *input, t_cli *cli);
void		child_process(t_cli *cli, t_com *com);

//****************************************************************************/
//* heredoc_utils.c

int			check_number_of_heredoc(t_com *com);
int			check_heredoc_error(t_cli *cli);

//****************************************************************************/
//* heredoc.c

int			create_heredoc_file(t_cli **cli);
int			ft_heredoc(t_cli *cli);

//****************************************************************************/
//* pwd.c

int			pwd(t_lst *mnsh, t_cli *cli);

//****************************************************************************/
//* unset.c

t_env		*freed_key_value(t_env *env);
void		delete_var(t_lst *mnsh, char *str);
int			ft_unset(char **str, t_lst **mnsh);

//****************************************************************************/
#endif