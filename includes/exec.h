/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:33:06 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/07/14 18:57:43 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "typedef.h"

//****************************************************************************/
//* check.c

int		check_commands(char **str, t_cli *cli);
int		check_if_fork(char **str, t_lst *mnsh, t_cli *cli);
int		check_if_path_needed(char **str);
int		sigpipe_checker(t_com *com);

//****************************************************************************/
//* child_utils.c

void	redirection_pipe(t_cli *cli);
void	redirection_fd(t_cli *cli);
void	redirection_parent(t_cli *cli);
void	redirection_error(t_cli *cli);
int		check_before_exec(t_cli **cli);

//****************************************************************************/
//* child.c

int		check_error(t_cli **cli);
int		fork_error(pid_t pid);
void	piping(t_cli *cli, int count);
void	execute_last_command(t_cli *cli);
int		redir(t_cli **cli);

//****************************************************************************/
//* exec_args.c

char	*check_parsing(char *str, t_cli *cli);
int		check_path_parsing(t_cli *cli);
int		update_command(t_cli *cli);
int		parsing_check(t_cli *cli);
int		get_nb_commands(t_com *com);

//****************************************************************************/
//* exec_utils.c

int		check_if_builtin(char *str);
char	*check_path(char *str, t_lst *mnsh);
int		find_path(t_env *env, t_lst *mnsh);
int		ft_error_path(char *str, char **path, t_lst *mnsh, char *full_path);
int		check_if_forked(t_cli *cli);

//****************************************************************************/
//* exec.c

void	main_loop(t_cli *cli, int count);
int		get_nb_pipes(t_token *token);
void	handle_heredoc(t_cli *cli, int *heredoc);
void	loop_commands(t_cli *cli, int *count);
int		exec_pipe(t_cli *cli);
int		check_er(t_cli *cli);

//****************************************************************************/
//* redirection.c

int		handle_redirection(t_cli **cli);
int		handle_error(int fd, t_cli *cli);
int		open_file(t_redirection *red);
int		handle_outfile(t_redirection *red, t_cli *cli);
int		handle_infile(t_redirection *red, t_cli *cli);
int		nf_handle_redirection(t_cli **cli);
void	heredoc_redirection(t_cli *cli);
int		check_redir_not_fork(t_cli *cli, int *ret);

//****************************************************************************/
//* signal.c

void	sig_ctrl_c(int signum);
void	sig_command_is_running(int signum);
void	heredoc_handler(int signum);
void	sig_ctrl_back(int signum);
void	handle_sig(int check);

//****************************************************************************/
//* exec_helpers.c

void	redirect_std(t_cli *cli, int heredoc);
void	wait_process(void);
void	reset_redir_values(t_cli *cli);

#endif