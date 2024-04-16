/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:46:22 by bapasqui          #+#    #+#             */
/*   Updated: 2024/04/16 12:49:02 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef LEXER_H
# define LEXER_H

typedef enum s_token_type
{
	COMMAND,
	CONTROLE_OPERATOR,
	REDIRECTION_OPERATOR,
	ARGUMENT
}						t_token_type;

//* *********************************************************************** *//
//* *********************************************************************** *//
//* 																		*//
//* 							CLI STRUCTURE								*//
//* 																		*//
//* *********************************************************************** *//
//* *********************************************************************** *//

//? https://www.gnu.org/software/bash/manual/bash.html
//? https://www.linux.org/threads/bash-01-script-basics.37797/#post-143818
//? https://www.linux.org/threads/bash-02-%E2%80%93-variables-and-such.38200/
//? https://www.linux.org/threads/bash-03-%E2%80%93-command-line-processing.38676/
//? https://se.ifmo.ru/~ad/Documentation/Bash_Shell/bash3-CHP-7-SECT-3.html

typedef struct s_arg
{
	char				*arg;
	struct s_arg		*next;
	struct s_arg		*prev;
}						t_arg;
typedef struct s_com
{
	char				*command;
	char				*path;
	t_arg				*arg;
	char				*redirection;
	int					type;
	int					index;
	struct s_com		*next;
	struct s_com		*prev;
}						t_com;

// TODO Parameter, Tilde, Word Splitting,Globbing
// TODO Possible add order variable in dlst

typedef struct s_variable
{
	char				*key;
	char				*value;
	char				*com_expansion;
	int					index;
	struct s_variable	*next;
	struct s_variable	*prev;
}						t_variable;

typedef struct s_token
{
	char				*token;
	t_token_type		type;
	int					index;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_cli
{
	char				*input;
	unsigned int		n_token;
	t_token				*token;
	t_com				*com;
	int					index;
	char				**meta;
	char				**redirect;
	char				**control;

}						t_cli;

//* *********************************************************************** *//
//* 																		*//
//* 							META-CHARACTERS								*//
//* 																		*//
//* *********************************************************************** *//
# define META_LIST ";,|,&,(,),<,>, ,\t,\n"
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
# define REDICRECT_OPERAT_LIST "<<,>>,<&,>|,<←,<>,>&,<,>"
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
# define CONTROL_OPERAT_LIST ";;&,||,&&,;;,;&,|&,(,),\n,|,&,;"
# define AND_AND "&&"
# define PIPE_PIPE "||"
# define SEMICOLON_AND ";&"
# define SEMICOLON_SEMICOLON_AND ";;&"
# define SEMICOLON_SEMICOLON ";;"
# define PIPE_AND "|&"

//* *********************************************************************** *//
//* *********************************************************************** *//
//* 																		*//
//* 								FUNCTION								*//
//* 																		*//
//* *********************************************************************** *//
//* *********************************************************************** *//

void			init_meta_and_operat(t_cli **cli);
void			split_into_token(t_cli *cli);
int 			ft_isstroperator(char *token, t_cli *cli);
t_token_type	token_type_discover(char *token, t_cli *cli);
int				get_position_of_next_meta(char *input);
void			free_cli(t_cli *cli);
char			*ft_strtrim_f(char *s1, char *set);


#endif