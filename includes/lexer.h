/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaiffie <ygaiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:46:22 by bapasqui          #+#    #+#             */
/*   Updated: 2024/05/03 08:39:55 by ygaiffie         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef LEXER_H
# define LEXER_H


typedef enum s_token_type
{
	COMMAND,
	CONTROLE_OPERATOR,
	REDIRECTION_OPERATOR,
	ARGUMENT,
	QUOTE,
	DQUOTE,
	BRACKET,
	FREEZE,
	HEREDOC,
	DELIMITER,
	IMMUTABLE,
	BUILTIN,
	KEYWORD
}	t_token_type;

//* *********************************************************************** *//
//* *********************************************************************** *//
//* 																		*//
//* 							CLI STRUCTURE								*//
//* 																		*//
//* *********************************************************************** *//
//* *********************************************************************** *//
//? https://www.gnu.org/software/bash/manual/html_node/Builtin-Index.html
//? https://www.gnu.org/software/bash/manual/bash.html
//? https://www.linux.org/threads/bash-01-script-basics.37797/#post-143818
//? https://www.linux.org/threads/bash-02-%E2%80%93-variables-and-such.38200/
//? https://www.linux.org/threads/bash-03-%E2%80%93-command-line-processing.38676/
//? https://se.ifmo.ru/~ad/Documentation/Bash_Shell/bash3-CHP-7-SECT-3.html

//* *********************************************************************** *//
//* 																		*//
//* 							META-CHARACTERS								*//
//* 																		*//
//* *********************************************************************** *//
# define META_LIST ";|&<> \t\n'\"{}[]()"
# define PIPE "|"
# define AND "&"
# define SEMICOLON ";"
# define OPEN_BRACKET "("
# define CLOSE_BRACKET ")"
# define GREATER_THAN ">"
# define LESS_THAN "<"
# define SPACE_META " "
# define TAB "\t"
# define NEWLINE "\n"

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
# define KEYWORD_LIST "if,then,else,elif,fi,case,esac,while,until,for,in,do,done"
# define OPEN_KEYWORD "if,while,until"

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
# define BUILTIN_LIST "alias,bg,bind,break,builtin,caller,cd,command,compgen,complete,compopt,continue,declare,dirs,disown,echo,enable,eval,exec,exit,export,fc,fg,getopts,hash,help,history,jobs,kill,let,local,logout,mapfile,popd,printf,pushd,pwd,read,readarray,readonly,return,set,shift,shopt,source,suspend,test,times,trap,type,typeset,ulimit,umask,unalias,unset,wait"


//* *********************************************************************** *//
//* *********************************************************************** *//
//* 																		*//
//* 								FUNCTION								*//
//* 																		*//
//* *********************************************************************** *//
//* *********************************************************************** *//

#endif