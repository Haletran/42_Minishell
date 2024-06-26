/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:18:10 by bapasqui          #+#    #+#             */
/*   Updated: 2024/06/26 15:37:23 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*LIBRAIRIES*/
# include "../libft/libft.h"
# include "builtins.h"
# include "command_line.h"
# include "dlst.h"
# include "exec.h"
# include "msg.h"
# include "parse.h"
# include "syntax_rules.h"
# include "typedef.h"
# include "utils.h"
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
# include <term.h>
# include <termios.h> // tcsetattr, tcgetattr
# include <unistd.h>  // write, access, close, fork, execve, dup, dup2, pipe

extern int	g_var;

# define RESET_SIG SIG_IGN
# define CTRL_C SIGINT
# define CTRL_BACKSLACH SIGQUIT
# define NOT_FOUND -5
# define ERROR -1
# define SUCCESS 0
# define STOPPED 1
# define NOT_EQUAL 90
# define FORK_FAILED -10
# define NO_FILE -20
# define IS_DIRECTORY -30
# define PERMISSION_DENIED -40

# ifndef DEBUG
#  define DEBUG 1
# endif

//* *********************************************************************** *//
//* 																		*//
//* 							META-CHARACTERS								*//
//* 																		*//
//* *********************************************************************** *//
# define META_LIST ";|&<> \t\n'\"{}[]()$"
# define PIPE "|"
# define AND "&"
# define SEMICOLON ";"
# define OPEN_BRACKET "("
# define CLOSE_BRACKET ")"
# define GREATER_THAN ">"
# define LESS_THAN "<"
# define SPACE_META " "
//# define TAB "\t"
//# define NEWLINE "\n"

//* *********************************************************************** *//
//* 																		*//
//* 						REDIRECTION OPERATOR							*//
//* 																		*//
//* *********************************************************************** *//
# define REDICRECT_OPERAT_LIST "<<,<&,<←,<>,>>,>|,>&,<,>"
# define DOUBLE_GREATER_THAN ">>"
# define GREATER_THAN_AND ">&"
# define LESS_THAN_GREATER_THAN "<>"
# define GREATER_THAN_PIPE ">|"
# define QQCHOSE "<←"
# define LESS_THAN_AND "<&"
# define DOUBLE_LESS_THAN "<<"

//* *********************************************************************** *//
//* 																		*//
//* 							CONTROL OPERATOR							*//
//* 																		*//
//* *********************************************************************** *//
# define CONTROL_OPERAT_LIST ";;&,;;,;&,||,|&,&&,(,),|,&,;,{,},[,]" //\n
# define AND_AND "&&"
# define PIPE_PIPE "||"
# define SEMICOLON_AND ";&"
# define SEMICOLON_SC_AND ";;&"
# define SEMICOLON_SC ";;"
# define PIPE_AND "|&"

//* *********************************************************************** *//
//* 																		*//
//* 								KEYWORD									*//
//* 																		*//
//* *********************************************************************** *//
# define OPEN_KEYWORD "if,while,until"
# define KEYWORD_LIST \
	"if,then,else,elif,fi,case,esac,while,until,for,in, \
	do,done"

//* *********************************************************************** *//
//* 																		*//
//* 							QUOTE & OTHER								*//
//* 																		*//
//* *********************************************************************** *//
# define QUOTE_LIST "',\""
# define BRACKET_LIST "{,},[,]"

//* *********************************************************************** *//
//* 																		*//
//* 							BUILTIN COMMAND								*//
//* 																		*//
//* *********************************************************************** *//
# define BUILTIN_LIST \
	"alias,bg,bind,break,builtin,caller,cd,command,compgen,complete,  \
	compopt,continue,declare,dirs,disown,echo,enable,eval,exec,exit, \
	export,fc,fg,getopts,hash,help,history,jobs,kill,let,local,      \
	logout,mapfile,popd,printf,pushd,pwd,read,readarray,readonly,   \
	return,set,shift,shopt,source,suspend,test,times,trap,type,      \
	typeset,ulimit,umask,unalias,unset,wait"

//* *********************************************************************** *//
//* 																		*//
//* 							SPECIAL PARAMETER							*//
//* 																		*//
//* *********************************************************************** *//
# define SPECIAL_PARAM_LIST "$*,$@,$#,$?,$!,$0,$_,$-,$$"

//* ************************************************************************ *//
//*                                                                          *//
//*                                 PROTOTYPES                               *//
//*                                                                          *//
//* ************************************************************************ *//

//* ************************************************************************ *//
//*                                                                          *//
//*                                 FUNCTIONS                                *//
//*                                                                          *//
//* ************************************************************************ *//

/*DEBUG*/
void		print_dlst(t_env *head);
void		print_all_in_cli(t_cli *cli);
void		print_all_token(t_token *token);
void		print_all_com(t_com *com);
void		debug(t_cli *cli, char *add_msg);
void		concat_no_space(t_cli *cli);
void		print_type(t_token *token);
void		print_type_com(t_com *com);
int			check_number_of_heredoc(t_com *com);
void		delete_file(char *str, t_cli *cli);
char		*check_parsing(char *str);
int			parsing_check(t_cli *cli);
int			check_redirection(t_cli *cli);
int			ft_exitcode(t_cli *cli, long int exit_code);
void		close_fds(void);
int			get_nb_commands(t_com *com);
void		print_error(int i, char *str);
int			gate_or(int i);

#endif