/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 01:23:53 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/06/20 10:57:20 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
	"minishell: syntax error near unexpected\
  token `newline'\n"
# define HEREDOC_MAX "minishell: maximum here-document count exceeded\n"
# define HEREDOC_EOF \
	"warning: here-document at line %d delimited by\
  end-of-file (wanted '%s')\n"
# define HEREDOC_CREATE "minishell: %s: %s\n"

#endif