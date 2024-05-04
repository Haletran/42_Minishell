/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:18:10 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/04 12:47:36 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*LIBRAIRIES*/
# include "../libft/libft.h"
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

extern int		g_var;
# define RESET_SIG SIG_IGN
# define CTRL_C SIGINT
# define CTRL_BACKSLACH SIGQUIT
# define NOT_FOUND -5
# define ERROR -1
# define SUCCESS 0
# define STOPPED 1

//* ************************************************************************ *//
//*                                                                          *//
//*                                 PROTOTYPES                               *//
//*                                                                          *//
//* ************************************************************************ *//

void			print_dlst(t_env *head);

//* ************************************************************************ *//
//*                                                                          *//
//*                                 FUNCTIONS                                *//
//*                                                                          *//
//* ************************************************************************ *//

//* CHECKS */
int				check_if_path_needed(char **str);
int				check_if_fork(char **str, t_lst *mnsh);
int				check_space(char *str);
int				check_commands(char **str, t_cli *cli);
int				check_if_pipe(char **str);
int				check_char(char *str, char c);
int				check_if_alpha(char *str);
char			*check_path(char *str, t_lst *mnsh);
int				check_if_path(char **envp);

//* FREE */
char			*free_char(char *str);
void			free_list(t_env **lst);
void			free_tab(char **str);
void			global_free(t_lst *mnsh, char **str);
void			free_command_line(t_cli *cli);
void			freeway(t_cli *cli);

//* GET */
int				get_nbargs(char **str);
int				get_len(char **str);
void			get_exit_code(t_lst *mnsh);
char			*get_env(char *str, t_lst *mnsh);

void			delete_node_env(t_env **head, t_env *del_node);
void			delete_all_nodes_env(t_env **head);
void			insert_env_front(t_env **head, char *key, char *value);
void			insert_env_after(t_env *prev_node, char *key, char *value);
void			insert_env_end(t_env **head, char *key, char *value);
char			*str_capitalizer(char *str);
char			*ft_join(char *s1, char *s2);
void			print_tab(char **src);
char			*strjoin(char *s1, char *s2);
void			print_tab(char **src);
int				exec_pipe(char **str, t_lst *mnsh);
char			**ft_split2(char *str, char *delim);
int				exec_and(char **str, t_lst *mnsh);
void			handle_sig(int check);
void			choose(t_cli *cli);
void			show_token(char **commands, t_com **com);
t_env			*sort_in_ascii(t_env *list);
char			**cpy(char **src, char **dest);
int				ft_cpy(char **dest, char **src);
void			print_list(char *string, t_env *env);
int				count_pipe(char **str);

//* INIT */
t_env			*init_stack(t_env *env, char **str);
int				init_array_env(t_cli **cli, char **envp);
int				init_array(t_cli **cli);
void			init_organizer(t_cli **cli, char **envp);
int				first_allocation(t_cli **cli, char **envp);
void			init_fd_history(t_cli **cli);
int				init_data_parsing(t_cli **cli);

/*BUILTS-INS*/
int				pwd(t_lst *mnsh);
int				ft_cd(char **str, t_lst *lst);
int				ft_echo(char **str, t_lst *mnsh);
int				ft_exit(char *code, t_cli *cli, char **str);
int				ft_env(t_lst *mnsh, char **str);
int				ft_export(t_lst *mnsh, char **str);
int				ft_unset(char **str, t_lst **mnsh);

/*BASH_UTILITIES*/
int				ft_heredoc(char **str, t_lst *mnsh);
void			sig_command_is_running(int signum);
void			ft_redirection(char **str, t_lst *mnsh);
void			sig_ctrl_back(int signum);
void			heredoc_handler(int signum);
int				delete(t_lst *mnsh, int len);
void			historyze(t_cli *cli);

/*LST*/
void			*ft_lst_new_2(char *index);
void			*ft_lstadd_back_2(t_env *lst, char *value);
void			print_list_export(t_lst *mnsh);
void			print_list_env(char *string, t_lst *mnsh);
int				print_path(char *str, t_lst *mnsh, int choose);
char			*search_path(char *str, t_lst *lst);
void			find_path_s(t_env *env, t_cli *cli);
void			find_path(t_env *env, t_lst *mnsh);
void			print_dlst(t_env *head);

int				exec_command(t_cli *cli);
int				exec(t_cli *cli);

/*PARSING*/
void			parsing_organiser(t_cli *cli);
char			*get_token_from_index(t_token *head, int index);
int				get_type_from_token(t_token *head, char *token);
void			delete_node_token(t_token **head, t_token *del_node);
void			delete_all_nodes_token(t_token **head);
void			insert_token_front(t_token **head, char *token,
					t_token_type type, int index);
void			insert_token_after(t_token *prev_node, char *token,
					t_token_type type, int index);
void			insert_token_end(t_token **head, char *token, t_token_type type,
					int index);
int				ft_ismeta(char c);
int				ft_iscontrol(char *token, t_cli *cli);
int				ft_isredirect(char *token, t_cli *cli);
int				get_last_index(t_token *head);
void			print_dlst_token(t_token *head);
void			tilde_expansion_process(t_token *tmp, char c, char *env_var);

char			*get_value_from_key(t_env *head, char *key);

void			delete_node_variable(t_variable **head, t_variable *del_node);
void			delete_all_nodes_variable(t_variable **head);
void			insert_variable_front(t_variable **head, char *key, char *value,
					int index);
void			insert_variable_after(t_variable *prev_node, char *key,
					char *value, int index);
void			insert_variable_end(t_variable **head, char *key, char *value,
					int index);
char			*get_variable_from_key(t_variable *head, char *key);
char			*get_key_from_variable(t_variable *head, char *variable);
int				get_last_index_var(t_variable *head);
void			print_dlst_variable(t_variable *head);
void			split_into_token(t_cli *cli);
int				ft_lenstrtype(char *token, t_cli *cli);
t_token_type	token_type_discover(char *token, t_cli *cli);
int				get_position_of_next_meta(char *input);
char			*ft_strtrim_f(char *s1, char *set);
void			input_reader(t_cli *cli);
void			tilde_expansion(t_cli *cli);
void			parameter_expansion(t_cli *cli);
int				varloc_creation(t_cli *cli);

int				ft_isthis(char *this, char c);
void			reindex_token_list(t_cli *cli);
void			glue_quotes(t_cli *cli);
void			remove_quotes(t_cli *cli);
void			cleaning_token_list(t_cli *cli);
void			delete_node_arg(t_arg **head, t_arg *del_node);
void			delete_all_nodes_arg(t_arg **head);
void			insert_arg_front(t_arg **head, char *arg);
void			insert_arg_after(t_arg *prev_node, char *arg);
void			insert_arg_end(t_arg **head, char *arg);
void			delete_node_com(t_com **head, t_com *del_node);
void			delete_all_nodes_com(t_com **head);
void			insert_com_front(t_com **head, char *command, int index);
void			insert_com_after(t_com *prev_node, char *command, int index);
void			insert_com_end(t_com **head, char *command, int index);
int				ft_error_path(char *str, char **path, t_lst *mnsh,
					char *full_path);
void			delete_all_nodes_variable(t_variable **head);
void			create_command(t_cli *cli);
t_token_type	quote_n_heredoc_census(char *token, t_cli *cli);
int				ft_lencmparray(char *token, char **array);
int				varloc_modify(t_cli *cli, char *key_line, char *var_line);
int				varloc_attrib(t_cli *cli, char *key_line, char *var_line,
					int index);
char			*variable_from_token(char *token);
char			*key_from_token(char *token);

/*RULES*/
void			rulers(t_cli *cli);
void			lt_rules(t_cli *cli, t_token *token);
void			redirect_rules(t_cli *cli, t_token *token);
void			syntax_error(t_cli *cli, char *token);
void			control_rules(t_cli *cli, t_token *token);

/*DEBUG*/

void			print_all_in_cli(t_cli *cli);
void			print_all_token(t_token *token);
void			print_all_arg(t_arg *arg);
void			print_all_com(t_com *com);

#endif