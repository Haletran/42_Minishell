/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 01:23:53 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/07/02 14:52:35 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSG_H
# define MSG_H

# define CD_TOO_MANY "cd : too many arguments\n"
# define CD_HOME_NOT "minishell : cd : HOME not set\n"
# define ENV_INV_OPT "env: invalid option -- '%c'\n"
# define ENV_NO_FILE "env: '%s': No such file or directory\n"
# define ENV_HELP "Try 'env --help' for more information.\n"
# define EXIT_MSG "exit\n"
# define EXIT_TOO_MANY "exit : too many arguments\n"
# define EXIT_NUM_REQ "exit : %s: numeric argument required\n"
# define EXPORT_NOT_VALID "minishell: export: '%s': not a valid identifier\n"
# define HEREDOC_SYNT \
	"minishell: syntax error near unexpected token `newline'\n"
# define HEREDOC_MAX "minishell: maximum here-document count exceeded\n"
# define HEREDOC_EOF \
	"warning: here-document at line %d delimited by end-of-file (wanted '%s')\n"
# define HEREDOC_CREATE "minishell: %s: %s\n"
# define CHECK_ER_ARG_REQ "minishell: %s: filename argument required\n"
# define CHECK_ER_USAGE "%s: usage: %s filename [arguments]\n"
# define CHECK_ER_CMD_NOT_FOUND "minishell: %s: command not found\n"
# define CHECK_ER_IS_DIR "minishell: %s: Is a directory\n"
# define SYNTAX_AMB "minishell: %s: ambiguous redirect\n"
# define BUILTINS_FREE SIGPIPE
# define SYNTAX_UNEXP "minishell: syntax error near unexpected token `%s'\n"
# define OLD_PWD_NOT "minishell: cd: OLDPWD not set\n"

#endif