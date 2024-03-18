/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:18:10 by bapasqui          #+#    #+#             */
/*   Updated: 2024/03/18 17:11:30 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*LIBRAIRIES*/
# include "../libft/libft.h"
# include "colors.h"
# include "lexer.h"
# include "struct.h"
# include <curses.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <dirent.h> // opendir, readdir, closedir
# include <errno.h>  // strerror, perror
# include <fcntl.h>  // open
# include <limits.h> // PATH_MAX
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>    // sigaction
# include <stdio.h>     // printf
# include <stdlib.h>    // malloc, free
# include <string.h>    // strerror
# include <sys/ioctl.h> // ioctl
# include <sys/stat.h>  // stat, lstat, fstat
# include <sys/types.h> // wait, waitpid, wait3, wait4, signal, sigemptyset,
# include <sys/wait.h>
# include <termios.h> // tcsetattr, tcgetattr
# include <unistd.h>  // write, access, close, fork, execve, dup, dup2, pipe
# include <unistd.h>  // unlink, chdir, getcwd

static int	g_value = 0;
# define RESET_SIG SIG_IGN
# define CTRL_C SIGINT
# define CTRL_BACKSLACH SIGQUIT
# define NOT_FOUND -5
# define ERROR -1
# define SUCCESS 0

/*FUNCTIONS*/
int			check_space(char *str);
char		*str_capitalizer(char *str);
char		*ft_join(char *s1, char *s2);
void		free_list(t_lst **lst);
void		free_tab(char **str);
int			exec(char **str, t_lst *args);
void		print_commands(char **src);
int			check_commands(char **str, t_lst *args);
int			get_nbargs(char **str);
char		*strjoin(char *s1, char *s2);
void		init_lst(t_lst **args, char **envp);
char		*check_path(char **str, t_lst *args, int nb);
void		get_exit_code(t_lst *args);
void		print_commands(char **src);
int			get_len(char **str);
int			exec_pipe(char **str, t_lst *args);
int			check_if_pipe(char **str);
int			check_char(char *str, char c);
char		**ft_split2(char *str, char *delim);
t_com		*init_stack(t_com *com, char **str);
int			check_if_and(char **str);
int			exec_and(char **str, t_lst *args);
void		handle_sig(int check);
void		choose(char *input, char **commands, t_lst **args);
void		show_token(char **commands, t_com **com);
char **sort_in_ascii(char **arr);

/*BUILTS-INS*/
int			pwd(t_lst *args);
int			ft_cd(char **str, t_lst *lst);
int	ft_echo(char **str, t_lst *args);
int			ft_exit(char *exit, t_lst *args);
int			ft_env(char **envp, char **str);
int			ft_export(t_lst *args, char **str);
int			ft_unset(char **str, t_lst *args);

/*BASH_UTILITIES*/
int			ft_heredoc(char **str);

#endif